spaceSplit :: String -> [String]
spaceSplit [] = [""]
spaceSplit (' ':xs) = "":spaceSplit xs
spaceSplit (x:xs) = let (s:ss) = spaceSplit xs in (x:s):ss

makeYesNo :: Bool -> String
makeYesNo True = "YES"
makeYesNo False = "NO"

solve :: Int -> Int -> Bool
solve n k
  | even n    = even notN 
  | otherwise = even isN
  where
    notN = k `div` 2
    isN = k - notN

tcs :: Int -> IO ()
tcs 0 = return () 
tcs t = do
    input2 <- getLine
    let (n:k:_) = map read (spaceSplit input2)
    putStrLn . makeYesNo . solve n $ k
    tcs (t-1)

main = do
    input1 <- getLine
    let t = read input1 :: Int
    tcs t
