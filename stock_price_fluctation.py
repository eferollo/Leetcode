from sortedcontainers import SortedList

class StockPrice:

    def __init__(self):
        self.prices_by_timestamp = {}
        self.sorted_prices = SortedList()
        self.latest_timestamp = 0

    def update(self, timestamp: int, price: int) -> None:
        if timestamp in self.prices_by_timestamp:
            old_price = self.prices_by_timestamp[timestamp]
            self.sorted_prices.remove(old_price)

        self.prices_by_timestamp[timestamp] = price
        self.sorted_prices.add(price)
        self.latest_timestamp = max(self.latest_timestamp, timestamp)

    def current(self) -> int:
        return self.prices_by_timestamp[self.latest_timestamp]

    def maximum(self) -> int:
        return self.sorted_prices[-1]

    def minimum(self) -> int:
        return self.sorted_prices[0]
        


# Your StockPrice object will be instantiated and called as such:
# obj = StockPrice()
# obj.update(timestamp,price)
# param_2 = obj.current()
# param_3 = obj.maximum()
# param_4 = obj.minimum()
