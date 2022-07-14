#Similar to Kadane's Algorithm, however:
#   Negative products are ok provided we can later get them back positive
#   We may need to restart from the current item if the previous one was 0 though.
#
# Therefore we maintain two "maximumExtendible" variables - one for the most positive and one for the most negative subarray we can get extending from the current item. 
# Then, when a negative item is encountered the two values end up swapping, and it is only the positiveExtendible one that is used to decide the overall best score
#We have to use Python here because the numbers can get reaaaaaaly big (see uDebug)

#First two lines are to run until EOF encountered
try: 
  while True:  
    
    zeroExists = False #flag to tell us if there is a zero in the set of numbers, as then zero is an acceptable answer
    nums = list(map(int,input().split()[:-1])) #array we take max sub product over

    #check if there is a zero
    for num in nums:
      if (num == 0):
        zeroExists = True

    #as described above
    maxExtendiblePositive = 0
    maxExtendibleNegative = 0
    bestProduct = -1e9

    # 1 linear pass over the numbers - O(n)
    for i in range(len(nums)):
      if (nums[i] > 0): #Positive number; don't swap
        maxExtendiblePositive = max(maxExtendiblePositive*nums[i],nums[i]) # may want to restart after 0 
        maxExtendibleNegative *= nums[i] 
      else: #<= 0; swap: +ve becomes -ve and vice versa
        mepOld = maxExtendiblePositive #we don't want the next line's update to propagate into the line after's update; we want previous values to be used so cache it in a temp variable.
        maxExtendiblePositive = maxExtendibleNegative*nums[i] #best positive is previous best negative times this negative number      
        maxExtendibleNegative = min(nums[i],mepOld*nums[i]) #may want to restart after 0; otherwise use this negative times previous best positive.
      
      bestProduct = max(maxExtendiblePositive,bestProduct) #only the positive products can get us the correct result

    #After the iteration over all numbers,
    if (bestProduct == 0 and not(zeroExists)): #We never altered maxExtendibleNegative from its starting value as it stayed 0 but there were no 0s in the set. Therefore there are no positive numbers in the set (just 1 negative number which we choose to output as a special case) 
      print(maxExtendibleNegative)
    else:
      print(bestProduct)

except EOFError:
  pass