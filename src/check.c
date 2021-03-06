#include "check.h"
#include "command.h"

int data_checking(char *coordinates) {

        int i, flag = 0;
        char abc[8] = {'a','b','c','d','e','f','g','h'};
        char numb[8] = {'1','2','3','4','5','6','7','8'};
       	
        for (i = 0; i < 8; i++) {
                if (coordinates[0] == abc[i]) 
                        flag++;
                if (coordinates[1] == numb[i])
                        flag++;
                if  (coordinates[2] == abc[i])
                        flag++;
                if (coordinates[3] == numb[i])
                        flag++;
        }
        if (flag != 4) {
        	printf("flag = %d\nОшибка данных\n", flag);
           return -1;      
        }
        if (flag == 4) {
            return 0;
        }
        return -1;
}

int move_checking(char m[8][8], int *c) {

    int i, j;
    if (m[c[1]][c[0]] == m[c[3]][c[2]])
        return 1;
    
//Пешка
if(m[c[1]][c[0]] == 'p' && (m[c[3]][c[2]] == '.')) {
        if(((c[0] - c[2]) == 0) && ((c[3] - c[1]) < 0)) {
            return 1;
        }
        if(((c[0] - c[2]) == 0) && ((c[3] - c[1]) > 2)) {
            return 1;
        }
        if(((c[2] - c[0]) != 0) && ((c[3] - c[1]) > 0)) {
            return 1;
        }
}

if(m[c[1]][c[0]] == 'P' && (m[c[3]][c[2]] == '.')) {
    if(((c[0] - c[2]) == 0) && ((c[1] - c[3]) < 0)) {
        return 1;
    }
    if(((c[0] - c[2]) == 0) && ((c[1] - c[3]) > 2)) {
        return 1;
    }
    if(((c[2] - c[0]) != 0) && ((c[3] - c[1]) < 0)) {
        return 1;
    }
}
if (m[c[1]][c[0]] == 'p' || m[c[1]][c[0]] == 'P') {
    if((m[c[1]][c[0]] == 'p' && m[c[3]][c[2]] == 'P') || (m[c[1]][c[0]] == 'P' && m[c[3]][c[2]] == 'p')) { 
       
        if (((c[0] + 1) == c[2]) && ((c[1] - 1) == c[3]))
            return 0;
        if (((c[0] + 1) == c[2]) && ((c[1] + 1) == c[3]))
            return 0;
        if (((c[0] - 1) == c[2]) && ((c[1] - 1) == c[3]))
            return 0;
        if (((c[0] - 1) == c[2]) && ((c[1] + 1) == c[3]))
            return 0;
    }
    if (m[c[3]][c[2]] == '.') {
        if (c[1] == 1 && c[3] < 4 && c[3] > 1 && c[0] == c[2] && m[c[1]+1][c[0]] == '.')
            return 0;
        if (c[1] == 6 && c[3] > 3 && c[3] < 6 && c[0] == c[2] && m[c[1]-1][c[0]] == '.')
            return 0;
        if (m[c[1]][c[0]] == 'p' && c[1] != 6 && c[3] == (c[1] - 1) && c[0] == c[2]) 
            return 0;
        if (m[c[1]][c[0]] == 'P' && c[1] != 1 && c[3] == (c[1] + 1) && c[0] == c[2])
            return 0;
    }
     return 0;
} 

//Ладья
if (m[c[1]][c[0]] == 'r' || m[c[1]][c[0]] == 'R') { 
    if(((c[0] - c[2]) != 0) && ((c[1] - c[3]) != 0)) {
        return 1;
    }    
    if (c[0] == c[2] && c[1] < c[3]) { 
        for (i = c[1] + 1; i < c[3]; i++)
            if (m[i][c[0]] != '.')
                return 1;
        return 0;
    }           
    if (c[0] == c[2] && c[1] > c[3]) { 
        for (i = c[3] + 1; i < c[1]; i++)
            if (m[i][c[0]] != '.')
                return 1;
        return 0;
    }
    if (c[0] < c[2] && c[1] == c[3]) {
        for (i = c[0] + 1; i < c[2]; i++)
            if (m[c[1]][i] != '.')
                return 1;
        return 0;
    }
    if (c[0] > c[2] && c[1] == c[3]) {
        for (i = c[2] + 1; i < c[0]; i++)
            if (m[c[1]][i] != '.')
                return 1;
        return 0;
    }
    return 0;
}
//Конь
if (m[c[1]][c[0]] == 'h' || m[c[1]][c[0]] == 'H') {
    if(((c[3] == (c[1] + 1)) || (c[3] == (c[1] - 1))) && (c[2] == (c[0] + 2) || (c[2] == (c[0] - 2))))
        return 0;
    if(((c[3] == (c[1] + 2)) || (c[3] == (c[1] - 2))) && ((c[2] == (c[0] + 1)) || (c[2] == (c[0] - 1))))
        return 0;
    return 1;
}

//Слон
if (m[c[1]][c[0]] == 'b' || m[c[1]][c[0]] == 'B') {
    if((c[1] - c[3]) == 0 && (c[0] - c[2]) != 0) {
        return 1;
    }
    if ((c[1] - c[3]) == (c[0] - c[2])) {
        i = c[1] - 1;
        j = c[0] - 1;
        while (i > c[3] && j > c[2]) {
            if(m[i][j] != '.')
                return 1;
                i--;
                j--;
        }
        return 0;
        }    
    if ((c[1] - c[3]) == (c[2] - c[0])) {
        i = c[1] - 1;
        j = c[0] + 1;
        while (i > c[3] && j < c[2]) {
            if(m[i][j] != '.')
                return 1;
                i--;
                j++;
        }
        return 0;
    }          
    if ((c[3] - c[1]) == (c[0] - c[2])) {
        i = c[1] + 1;
        j = c[0] - 1;
        while (i < c[3] && j > c[2]) {
            if(m[i][j] != '.')
                return 1;
                i++;
                j--;
        }
        return 0;
    }  
    if ((c[3] - c[1]) == (c[2] - c[0])) {
        i = c[1] + 1;
        j = c[0] + 1;
        while (i < c[3] && j < c[2]) {
            if(m[i][j] != '.')
                return 1;
                i++;
                j++;
        }
        return 1;
    }  
    return 0;
}
//Король
if(m[c[1]][c[0]] == 'k' || m[c[1]][c[0]] == 'K') {
    if (((c[3] - c[1] == 1) || (c[1] - c[3] == 1)) && (c[2] == c[0]))
        return 0;
    if ((c[1] == c[3]) && ((c[0] - c[2] == 1) || (c[2] - c[0]) == 1))
        return 0;
    if ((c[3] - c[1] == 1) && ((c[2] - c[0] == 1) || (c[0] - c[2] == 1)))
        return 0;
    if ((c[1] - c[3] == 1) && ((c[2] - c[0] == 1) || (c[0] - c[2] == 1)))
        return 0;
    return 1;
}
//Королева
if(m[c[1]][c[0]] == 'q' || m[c[1]][c[0]] == 'Q') {
    if(((c[3] - c[1]) != 0) && ((c[0] - c[2]) != 0)) {
        return 0;
    }
    if(((c[3] - c[1]) == 0) && ((c[0] - c[2]) != 0)) {
        return 0;
    }
    if (c[0] == c[2] && c[1] < c[3]) { 
        for (i = c[1] + 1; i < c[3]; i++)
            if (m[i][c[0]] != '.')
                return 1;
        return 0;
    }
    if (c[0] == c[2] && c[1] > c[3]) { 
        for (i = c[3] + 1; i < c[1]; i++)
            if (m[i][c[0]] != '.')
                return 1;
        return 0;
    }
    if (c[0] < c[2] && c[1] == c[3]) {
        for (i = c[0] + 1; i < c[2]; i++)
            if (m[c[1]][i] != '.')
                return 0;
        return 1;
    }
    if (c[0] > c[2] && c[1] == c[3]) {
        for (i = c[2] + 1; i < c[0]; i++)
            if (m[c[1]][i] != '.')
                return 0;
        return 1;
    }
    if ((c[1] - c[3]) == (c[0] - c[2])) {
        i = c[1] - 1;
        j = c[0] - 1;
        while (i > c[3] && j > c[2]) {
            if(m[i][j] != '.')
                return 0;
                i--;
                j--;
        }
        return 1;
    }    
    if ((c[1] - c[3]) == (c[2] - c[0])) {
        i = c[1] - 1;
        j = c[0] + 1;
        while (i > c[3] && j < c[2]) {
            if(m[i][j] != '.')
                return 0;
                i--;
                j++;
        }
        return 1;
    }          
    if ((c[3] - c[1]) == (c[0] - c[2])) {
        i = c[1] + 1;
        j = c[0] - 1;
        while (i < c[3] && j > c[2]) {
            if(m[i][j] != '.')
                return 0;
                i++;
                j--;
        }
        return 1;
    }  
    if ((c[3] - c[1]) == (c[2] - c[0])) {
        i = c[1] + 1;
        j = c[0] + 1;
        while (i < c[3] && j < c[2]) {
            if(m[i][j] != '.')
                return 0;
                i++;
                j++;
        }
        return 1;
    }  
}
    return 0;
}

void moving(char m[8][8], int *c) {
        int buffer;
        if (m[c[3]][c[2]] == '.') {
            buffer = m[c[1]][c[0]];
            m[c[1]][c[0]] = m[c[3]][c[2]];
            m[c[3]][c[2]] = buffer;
            showboard(m);
        } else {
            m[c[3]][c[2]] = m[c[1]][c[0]];
            m[c[1]][c[0]] = '.';
            m[c[1]][c[0]] = '.';
            showboard(m);
          }
}    


