#include "../include/Market.h"
#include "../include/Entity.h"
Market::Market() {
    for (int i = 0; i < TYPELENGTH; i++)
    {
        stock[i] = 0;
        avgPrice[i] = -1;

        transactionCount[i] = 0;
        avgTransactionPrice[i] = 0.f;
        requestCount[i] = 0.f;
        supplyCount[i] = 0.f;
    }
}
Market::~Market() {
}
void Market::prepare() {
    for (int i = 0; i < TYPELENGTH; i++)
    {
        transactionCount[i] = 0;
        avgTransactionPrice[i] = 0.f;
        requestCount[i] = 0.f;
        supplyCount[i] = (float)stock[i];
    }
}
void Market::update() {
    removeInvalidGoods();

    //For the cargos that are failed to sell, update their price, so that the longer the item stay in the market,
    //The cheaper it is, so to sell out.
    for (int i = 0; i < TYPELENGTH; i++)
    {
        for (int j = 0; j < goods[i].size(); j++)
        {
            if(goods[i].at(j).second> MAX_INITIAL_PRICING/10/5)
                goods[i].at(j).second -= Utility::random(1, MAX_INITIAL_PRICING /10/5);
        }
    }
    avgPricing();
}
void Market::avgPricing() {
    //Also calculate the avg transcation price
    for (int i = 0; i < TYPELENGTH; i++)
    {
        int sum = 0;
        if (stock[i] < 1) {
            //avgPrice[i] = -1;
            continue;
        }
        for (int j=0;j<goods[i].size();j++)
        {
            sum += goods[i].at(j).second;
        }
        avgPrice[i] = (sum / stock[i]);
        if (transactionCount[i] > 0) {
            avgTransactionPrice[i] /= (float)transactionCount[i];
        }
        else {
            avgTransactionPrice[i] = 0.f;
        }
    }
}

void Market::registerGood(Entity* owner, item_type type, int price)
{
    goods[type].emplace_back(owner,price);
    stock[type]++;
    supplyCount[type]++;
}
int Market::buyGood(Entity* buyer, item_type type, int cash) {
    requestCount[type]+=0.2;
    //cash argument is the maximum cash the buyer is willing to pay
    if (cash < 1||stock[type]<1) {
        return -1;
    }
    //Randomly pick 3 items from the market of the type, and buy the cheapest one, since the product quality is the same
    int picked[AMOUNT_TO_COMPARE];
    int r, price, minPrice, minIdx;
    for (int i = 0; i < AMOUNT_TO_COMPARE; i++)
    {
        r = Utility::random(0,(stock[type]-1));
        picked[i] = r;
    }
    minPrice = goods[type].at(picked[0]).second;
    minIdx = picked[0];
    for (int i = 1; i < AMOUNT_TO_COMPARE; i++)
    {
        price = goods[type].at(picked[i]).second;
        if (price < minPrice)
        {
            minPrice = price;
            minIdx = picked[i];
        }
    }
    if (cash < minPrice)
        return -1;
    //Buy the minIdx one, and return the single price to the buyer
    //Add the good to the buyer
    buyer->cash -= minPrice;
    buyer->itemCount[type]++;
    //Remove the good from the market and send the money to the owner
    Entity* owner = goods[type].at(minIdx).first;
    owner->cash += minPrice; owner->income += minPrice;
    owner->itemPrice[type] = minPrice + Utility::random(1, MAX_INITIAL_PRICING / 10); //Update the expectation of selling of the owner
    goods[type].erase(goods[type].begin() + minIdx);
    stock[type]--;
    requestCount[type] += 0.8;

    transactionCount[type]++;
    avgTransactionPrice[type] += minPrice;
    return minPrice;
}

void Market::removeInvalidGoods()
{
    for (int i = 0; i < TYPELENGTH; i++)
    {
        for (auto it = goods[i].begin(); it != goods[i].end();)
        {
            Entity* owner = it->first;
            if (owner->isDead)
            {
                // Owner is no longer valid, remove the corresponding good from the market
                it = goods[i].erase(it);
                stock[i]--;
            }
            else {
                ++it;
            }
        }
    }
}