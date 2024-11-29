int maxProfit(int* prices, int pricesSize) {
    int i, j, profit, min, max_profit;
    
    min = prices[0];
    max_profit = 0;
    for(i = 1; i < pricesSize; i++) {
        if(prices[i] < min) {
            min = prices[i];
        }    
        
        profit = prices[i] - min;
        if(profit > max_profit) {
            max_profit = profit;
        }
    }
    return max_profit; 
}
