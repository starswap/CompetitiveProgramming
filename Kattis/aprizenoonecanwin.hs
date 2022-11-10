import Data.List (sort)

main = do
    line1 <- getLine
    let [n,c] = map (\x -> read x :: Integer) (words line1)
    line2 <- getLine
    let costs = sort $ map (\x -> read x :: Integer) (words line2)
    let okCosts = takeWhile (\(x,y) -> x+y <= c ) (zip costs (tail costs))
    print (1 + length okCosts)


