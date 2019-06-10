/**
 * Created by omerc on 6/9/2019.
 */

import java.util.*;
import java.util.function.Function;

class BoardUtil
{
    final static int MAX = 8;

    static class Pair {
        int row;
        int column;

        Pair(int r, int c) {
            row = r;
            column = c;
        }
    }

    static boolean board[][] = {
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
            {false, false, false, false, false, false, false, false},
    };

    public static boolean hasCollision(int row, int col, Function<Integer, Integer> rowfunc, Function<Integer, Integer> colfunc) {
        int nr = rowfunc.apply(row);
        int nc = colfunc.apply(col);

        return ((nr >= 0 && nr < MAX && nc >= 0 && nc < MAX) &&
                (BoardUtil.board[nr][nc] || hasCollision(nr, nc, rowfunc, colfunc))
        );
    }

    public static boolean hasCollision(int row, int col) {
        Function<Integer, Function<Integer, Integer>> func = a -> b -> a + b;
        Function<Integer, Integer> inc = func.apply(1);
        Function<Integer, Integer> dec = func.apply(-1);
        Function<Integer, Integer> nochg = func.apply(0);

        return hasCollision(row, col, dec, dec) ||
                hasCollision(row, col, dec, inc) ||
                hasCollision(row, col, nochg, dec) ||
                hasCollision(row, col, dec, nochg);
    }
}

class RecursiveEightQueen {
    static int num = 0;
    public void placeQueen(int row, ArrayList<BoardUtil.Pair> path) {
        if (row == BoardUtil.MAX) {
            System.out.print(++num);
            for (BoardUtil.Pair j : path) {
                System.out.print(": (" + j.row + "," + j.column + ")");
            }
            System.out.println();
            return;
        }

        for (int col = 0; col < BoardUtil.MAX; ++col) {
            if (BoardUtil.hasCollision(row, col)) {
                continue;
            }

            // Setup
            BoardUtil.board[row][col] = true;
            path.add(new BoardUtil.Pair(row, col));

            placeQueen(row + 1, path);

            // TearDown
            path.remove(path.size() - 1);
            BoardUtil.board[row][col] = false;
        }
    }
}

class NonRecursiveEightQueen
{
    Stack<BoardUtil.Pair> stack = new Stack<>();
    ArrayList<BoardUtil.Pair> path = new ArrayList<>();
    int num = 0;

    public void placeQueens() {

        // insert a dummy 0,-1 entry, so that first pop will work.
        stack.push(new BoardUtil.Pair(0, -1));

        while(!stack.empty()){
            BoardUtil.Pair pair = stack.pop();

            int lastRow = pair.row;
            int lastCol = pair.column;

            if (lastRow == BoardUtil.MAX-1) {
                // Success.
                System.out.print(++num);
                for (BoardUtil.Pair j : path) {
                    System.out.print(": (" + j.row + "," + j.column + ")");
                }
                System.out.println();
            }

            if (lastCol != -1) {
                // TearDown
                BoardUtil.board[lastRow][lastCol] = false;
                path.remove(path.size() - 1);
            }

            int newCol = lastCol + 1;
            if (newCol >= BoardUtil.MAX){
                continue;
            }

            placeQueenTillPossible(lastRow, newCol);
        }
    }

    private void placeQueenTillPossible(int row, int col) {
        boolean success = tryPlaceQueenInRow(row, col);
        if (!success) {
            return;
        }

        for (int i = row+1; i < BoardUtil.MAX; ++i) {
            success = tryPlaceQueenInRow(i, 0);
            if (!success) {
                return;
            }
        }
    }

    private boolean tryPlaceQueenInRow(int row, int startCol) {
        for (int col = startCol; col < BoardUtil.MAX; ++col) {
            if (tryPush(row, col)) {
                return true;
            }
        }
        return false;
    }

    private boolean tryPush(int row, int col) {
        if (BoardUtil.hasCollision(row, col)) {
            return false;
        }

        stack.push(new BoardUtil.Pair(row, col));

        // Setup
        BoardUtil.board[row][col] = true;
        path.add(new BoardUtil.Pair(row, col));

        return true;
    }
}

public class Eight {
    public static void main(String[] args) {
        //RecursiveEightQueen recursiveQueen = new RecursiveEightQueen();
        //ArrayList<BoardUtil.Pair> path = new ArrayList<>();
        //recursiveQueen.placeQueen(0, path);

        NonRecursiveEightQueen nonrecursiveEightQueen = new NonRecursiveEightQueen();
        nonrecursiveEightQueen.placeQueens();
    }
}
