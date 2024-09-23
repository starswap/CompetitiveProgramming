{-# LANGUAGE NumericUnderscores #-}
import Control.Monad (forM_, replicateM)
import Data.Tuple (swap)

data Colour = R | B deriving Show
data RBTree = E | N Colour RBTree Int RBTree Int Int deriving Show -- nodes in subtree including self,  lazy minus

lmap :: (RBTree -> RBTree) -> RBTree -> RBTree
lmap f E                  = E
lmap f (N c l v r n lazy) = N c (f l) v r n lazy

rmap :: (RBTree -> RBTree) -> RBTree -> RBTree
rmap f E                  = E
rmap f (N c l v r n lazy) = N c l v (f r) n lazy

nodes :: RBTree -> Int
nodes E               = 0
nodes (N _ _ _ _ n _) = n

propagate :: RBTree -> RBTree
propagate E = E
propagate (N c E v E n lazy)
  = N c E (v - lazy) E n 0
propagate (N c (N lc ll lv lr ln llazy) v E n lazy)
  = N c (N lc ll lv lr ln (llazy + lazy)) (v - lazy) E n 0
propagate (N c E v (N rc rl rv rr rn rlazy) n lazy)
  = N c E (v - lazy) (N rc rl rv rr rn (rlazy + lazy)) n 0
propagate (N c (N lc ll lv lr ln llazy) v (N rc rl rv rr rn rlazy) n lazy)
  = N c (N lc ll lv lr ln (llazy + lazy)) (v - lazy) (N rc rl rv rr rn (rlazy + lazy)) n 0

recursivePropagate :: RBTree -> RBTree
recursivePropagate t =
    case propagate t of
        E                  -> E
        (N c l v r n lazy) -> N c (recursivePropagate l) v (recursivePropagate r) n lazy

balance :: RBTree -> RBTree
balance E = E
balance t = go c lt x rt n
  where
    (N c lt x rt n _) = propagate t

    go :: Colour -> RBTree -> Int -> RBTree -> Int -> RBTree
    go B left z d nz
      | (N R (N R a x b nx lx) y c ny ly) <- lmap propagate (propagate left)  = N R (N B a x b (nodes a + nodes b + 1) 0) y (N B c z d (nodes c + nodes d + 1) 0) nz 0
      | (N R a x (N R b y c ny ly) nx lx) <- rmap propagate (propagate left)  = N R (N B a x b (nodes a + nodes b + 1) 0) y (N B c z d (nodes c + nodes d + 1) 0) nz 0
    go B a x right nx
      | (N R (N R b y c ny ly) z d nz lz) <- lmap propagate (propagate right) = N R (N B a x b (nodes a + nodes b + 1) 0) y (N B c z d (nodes c + nodes d + 1) 0) nx 0
      | (N R b y (N R c z d nz lz) ny ly) <- rmap propagate (propagate right) = N R (N B a x b (nodes a + nodes b + 1) 0) y (N B c z d (nodes c + nodes d + 1) 0) nx 0
    go c lt x rt n = N c lt x rt n 0

blacken :: RBTree -> RBTree
blacken (N R lt x rt n l) = N B lt x rt n l
blacken t = t

insert :: Int -> RBTree -> RBTree
insert x t = blacken (go t)
  where
    go E = N R E x E 1 0
    go t
      | x < y     = balance (N c (go lt) y rt (n + 1) 0)
      | x > y     = balance (N c lt y (go rt) (n + 1) 0)
      | otherwise = t'                                    -- x == y
      where
        t'@(N c lt y rt n l) = propagate t

decrementSmallestN :: Int -> RBTree -> RBTree
decrementSmallestN n (N c l v r m lazy)
  | n == m                = N c l v r m (lazy + 1)
  | n < m && n <= nodes l = N c (decrementSmallestN n l) v r m lazy
  | n < m && n >  nodes l = N c (decrementSmallestN (nodes l) l) (v - 1) (decrementSmallestN (n - nodes l - 1) r) m lazy
  | otherwise             = error "Tried to decrement more nodes than in the tree"
decrementSmallestN 0 E    = E
decrementSmallestN n E    = error "Tried to decrement nodes in an empty tree"

toList :: RBTree -> [Int]
toList t =
    case propagate t of
        E                  -> []
        (N c l v r n lazy) -> toList l ++ [v] ++ toList r

-- number of nodes less than or equal to this value
rank :: Int -> RBTree -> Int
rank x t =
  case propagate t of
    E                              -> 0
    (N c l v r n lazy) | x < v     -> rank x l
    (N c l v r n lazy) | x > v     -> nodes l + 1 + rank x r
    (N c l v r n lazy) | otherwise -> nodes l + 1           -- x == v
  
findInsertPos :: RBTree -> Int -> Int
findInsertPos t e = go (-1) 2_000_000
    where
        go :: Int -> Int -> Int
        go lo hi
          | hi - lo <= 1   = hi
          | final_pos > mi = go mi hi
          | final_pos < mi = go lo (mi - 1)
          | otherwise      = go lo mi
          where mi        = (hi + lo) `div` 2
                boost     = rank mi t
                final_pos = e + boost

processStone :: RBTree -> Int -> RBTree
processStone t e = insert n (decrementSmallestN r t)
  where n = findInsertPos t e
        r = rank n t 

getClosestStone :: Int -> Int -> [Int] -> (Int, Int)
getClosestStone n g es = swap . minimum $ candidates
  where candidates = zipWith (\e i -> (abs (g - e), i)) es [n, n - 1 .. 1]

solve :: Int -> Int -> [Int] -> (Int, Int)
solve n g es = getClosestStone n g (toList (foldl processStone E es))

spaceSplit :: String -> [String]
spaceSplit [] = [""]
spaceSplit (' ':xs) = "":spaceSplit xs
spaceSplit (x:xs) = let (s:ss) = spaceSplit xs in (x:s):ss

lineOfIntegers :: IO [Int]
lineOfIntegers = map read . spaceSplit <$> getLine

nIntegerLines :: Int -> IO [Int]
nIntegerLines n = replicateM n (read <$> getLine)

tcToString :: Int -> Int -> Int -> String
tcToString t n dist = "Case #" ++ show t ++ ": " ++ show n ++ " " ++ show dist

solveTc :: Int -> IO ()
solveTc i = do
  (n:g:_) <- lineOfIntegers
  es      <- nIntegerLines n
  putStrLn (uncurry (tcToString i) (solve n g es))

solveAll :: Int -> IO ()
solveAll n = mapM_ solveTc [1..n]

main = getLine >>= solveAll . read
