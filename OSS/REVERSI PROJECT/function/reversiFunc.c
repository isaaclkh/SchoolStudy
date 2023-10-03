#include "../reversi.h"

#define WHITE 0
#define BLACK 1

#define FALSE 0
#define TRUE 1

int has_valid_move = FALSE;

int is_valid_position(int i, int j)
{
    if (i < 0 || i >= 8 || j < 0 || j >= 8)
        return FALSE;
    return TRUE;
}

int distance(int i1, int j1, int i2, int j2)
{
    int di = abs(i1 - i2), dj = abs(j1 - j2);
    if (di > 0)
        return di;
    return dj;
}

int is_playable(int i, int j)
{
    memset(playable_direction[i][j], 0, 8);

    if (!is_valid_position(i, j)) return FALSE;
    if (board[i][j] != 2) return FALSE;
    
    int playable = FALSE;
    int opposing_player = (current_player + 1) % 2;

    // Test UL diagonal
    int i_it = i - 1, j_it = j - 1;

    while (is_valid_position(i_it, j_it) && board[i_it][j_it] == opposing_player)
    {
        i_it -= 1;
        j_it -= 1;
    }

    if (is_valid_position(i_it, j_it) && distance(i, j, i_it, j_it) > 1 && board[i_it][j_it] == current_player)
    {
        playable_direction[i][j][0] = 1;
        playable = TRUE;
    }

    // Test UP path
    i_it = i - 1, j_it = j;
    while (is_valid_position(i_it, j_it) && board[i_it][j_it] == opposing_player) i_it -= 1;

    if (is_valid_position(i_it, j_it) && distance(i, j, i_it, j_it) > 1 && board[i_it][j_it] == current_player)
    {
        playable_direction[i][j][1] = 1;
        playable = TRUE;
    }

    // Test UR diagonal
    i_it = i - 1, j_it = j + 1;
    while (is_valid_position(i_it, j_it) && board[i_it][j_it] == opposing_player)
    {
        i_it -= 1;
        j_it += 1;
    }
    if (is_valid_position(i_it, j_it) && distance(i, j, i_it, j_it) > 1 && board[i_it][j_it] == current_player)
    {
        playable_direction[i][j][2] = 1;
        playable = TRUE;
    }

    // Test LEFT path
    i_it = i, j_it = j - 1;
    while (is_valid_position(i_it, j_it) && board[i_it][j_it] == opposing_player)
        j_it -= 1;

    if (is_valid_position(i_it, j_it) && distance(i, j, i_it, j_it) > 1 && board[i_it][j_it] == current_player)
    {
        playable_direction[i][j][3] = 1;
        playable = TRUE;
    }

    // Test RIGHT path
    i_it = i, j_it = j + 1;
    while (is_valid_position(i_it, j_it) && board[i_it][j_it] == opposing_player)
        j_it += 1;

    if (is_valid_position(i_it, j_it) && distance(i, j, i_it, j_it) > 1 && board[i_it][j_it] == current_player)
    {
        playable_direction[i][j][4] = 1;
        playable = TRUE;
    }

    // Test DL diagonal
    i_it = i + 1, j_it = j - 1;
    while (is_valid_position(i_it, j_it) && board[i_it][j_it] == opposing_player)
    {
        i_it += 1;
        j_it -= 1;
    }
    if (is_valid_position(i_it, j_it) && distance(i, j, i_it, j_it) > 1 && board[i_it][j_it] == current_player)
    {
        playable_direction[i][j][5] = 1;
        playable = TRUE;
    }

    // Test DOWN path
    i_it = i + 1, j_it = j;
    while (is_valid_position(i_it, j_it) && board[i_it][j_it] == opposing_player)
        i_it += 1;

    if (is_valid_position(i_it, j_it) && distance(i, j, i_it, j_it) > 1 && board[i_it][j_it] == current_player)
    {
        playable_direction[i][j][6] = 1;
        playable = TRUE;
    }

    // Test DR diagonal
    i_it = i + 1, j_it = j + 1;
    while (is_valid_position(i_it, j_it) && board[i_it][j_it] == opposing_player)
    {
        i_it += 1;
        j_it += 1;
    }
    if (is_valid_position(i_it, j_it) && distance(i, j, i_it, j_it) > 1 && board[i_it][j_it] == current_player)
    {
        playable_direction[i][j][7] = 1;
        playable = TRUE;
    }
    return playable;
}

void mark_playable_positions()
{
    has_valid_move = FALSE;
    for (int i = 0; i < 8; ++i)
    {
        for (int j = 0; j < 8; ++j)
        {
            if (board[i][j] == 3)
                board[i][j] = 2;
            if (is_playable(i, j))
            {
                board[i][j] = 3;
                has_valid_move = TRUE;
            }
        }
    }
}

void capture_pieces(int i, int j)
{
    int opposing_player = (current_player + 1) % 2;
    int i_it, j_it;

    // Capture UL diagonal
    if (playable_direction[i][j][0])
    {
        i_it = i - 1, j_it = j - 1;
        while (board[i_it][j_it] == opposing_player)
        {
            board[i_it][j_it] = current_player;
            scores[current_player]++;
            scores[opposing_player]--;
            i_it -= 1;
            j_it -= 1;
        }
    }

    // Capture UP path
    if (playable_direction[i][j][1])
    {
        i_it = i - 1, j_it = j;
        while (board[i_it][j_it] == opposing_player)
        {
            board[i_it][j_it] = current_player;
            scores[current_player]++;
            scores[opposing_player]--;
            i_it -= 1;
        }
    }

    // Capture UR diagonal
    if (playable_direction[i][j][2])
    {
        i_it = i - 1, j_it = j + 1;
        while (board[i_it][j_it] == opposing_player)
        {
            board[i_it][j_it] = current_player;
            scores[current_player]++;
            scores[opposing_player]--;
            i_it -= 1;
            j_it += 1;
        }
    }

    // Capture LEFT path
    if (playable_direction[i][j][3])
    {
        i_it = i, j_it = j - 1;
        while (board[i_it][j_it] == opposing_player)
        {
            board[i_it][j_it] = current_player;
            scores[current_player]++;
            scores[opposing_player]--;
            j_it -= 1;
        }
    }

    // Capture RIGHT path
    if (playable_direction[i][j][4])
    {
        i_it = i, j_it = j + 1;
        while (board[i_it][j_it] == opposing_player)
        {
            board[i_it][j_it] = current_player;
            scores[current_player]++;
            scores[opposing_player]--;
            j_it += 1;
        }
    }

    // Capture DL diagonal
    if (playable_direction[i][j][5])
    {
        i_it = i + 1, j_it = j - 1;
        while (board[i_it][j_it] == opposing_player)
        {
            board[i_it][j_it] = current_player;
            scores[current_player]++;
            scores[opposing_player]--;
            i_it += 1;
            j_it -= 1;
        }
    }

    // Capture DOWN path
    if (playable_direction[i][j][6])
    {
        i_it = i + 1, j_it = j;
        while (board[i_it][j_it] == opposing_player)
        {
            board[i_it][j_it] = current_player;
            scores[current_player]++;
            scores[opposing_player]--;
            i_it += 1;
        }
    }

    // Capture DR diagonal
    if (playable_direction[i][j][7])
    {
        i_it = i + 1, j_it = j + 1;
        while (board[i_it][j_it] == opposing_player)
        {
            board[i_it][j_it] = current_player;
            scores[current_player]++;
            scores[opposing_player]--;
            i_it += 1;
            j_it += 1;
        }
    }
}

void display_winner()
{
    printf("Final score:\n%s: %d %s: %d\n", "RED", scores[0], "BLUE", scores[1]);
    if (scores[0] > scores[1])
        printf("%s wins.\n", "READ");
    else if (scores[0] < scores[1])
        printf("%s wins.\n", "BLUE");
    else
        printf("Draw game.\n");
}

int checkEnd(){
    int check = 1;

    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            if(board[i][j] == 1 || board[i][j] == 2) check = 0;
        }
    }

    return !(check);
}

int make_next_move(int x, int y)
{
    int row = x;
    int col = y;

    if (is_valid_position(row, col) && board[row][col] == 3)
    {
        board[row][col] = current_player;
        scores[current_player]++;
        capture_pieces(row, col);
        return 1;
    }
    else return -1;
}