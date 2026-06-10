class Solution(object):
    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """
        hash_table = {}

        for i, val in enumerate(nums):
            complement = target - val
            if complement in hash_table:
                return [hash_table[complement], i]
            hash_table[val] = i
        
        return None
