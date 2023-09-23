/*
Conway's Game of Life

~Andrea-Tomatis
*/

void init_mat(bool*** mat, int dim){
    
    *mat = (bool**) malloc(dim * sizeof(bool*));

    for(int i = 0; i < dim; i++){
        (*mat)[i] = (bool*) malloc(dim * sizeof(bool));

        for (int j = 0; j < dim; j++)
            (*mat)[i][j] = false;
    }

}


void print_mat(bool** mat, int dim){
    for(int i = 0; i < dim; i++){
        for(int j = 0; j < dim; j++){
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return;
}



int read_from_file(bool ***mat){

    int fp, i = 0, j = 0;
    char* fn = "./matrix.txt";
    char buf;

    if((fp = open(fn, O_RDONLY)) == -1)
        return -1;


    while(read(fp, &buf, 1) != 0 && i < DIM){
        if (isdigit(buf)){
            (*mat)[i][j++] = atoi(&buf);
            
            if (j == DIM){
                i++;
                j = 0;
            }
        }
    }


    close(fp);
    return 0;
}


void start_cond(bool ***mat){

    if (read_from_file(mat) != -1)
        return;

    bool stop = false;
    int x,y;

    printf("Insert every position you want to fill:\n");
    while(!stop){
        
        printf("x: ");
        scanf("%d",&x);
        
        printf("y: ");
        scanf("%d",&y);

        if (x <= 0 || x > DIM || y <= 0 || y > DIM)
            stop = true;
        else
            (*mat)[x-1][y-1] = true;
    }
}


int rules(bool **mat, int x, int y, int dim){
    int n = 0;
    
    for (int i = x-1; i <= x+1; i++){
        for (int j = y-1; j <= y+1; j++){
            
            if (!(i == x && j == y) && 
                (i >= 0 && i < dim) &&
                (j >= 0 && j < dim)){
                    if (mat[i][j])
                        n++;
            }
        }
    }

    return n;
}


void matriscopy (bool ** destmat, bool ** srcmat) 
{
  //memcpy(destmat,srcmat, DIM*DIM*sizeof(int));
  for (int i = 0; i < DIM; i++) {
        for (int j = 0; j < DIM; j++) {
            destmat[i][j] = srcmat[i][j];
        }
    }
}


int equal(bool **mat1, bool **mat2, int dim){
    
    int n = 0;
    for(int i = 0; i < dim; i++)
        for (int j = 0; j < dim; j++)
            if (mat1[i][j] ^ mat2[i][j])
                n++;
    return n;
}


bool update(bool ***mat, int dim){

    int change;
    bool **new_mat;


    init_mat(&new_mat, dim);

    matriscopy(new_mat, *mat);


    for (int i = 0; i < dim; i++){
        for (int j = 0; j < dim; j++){    
            
            int ans = rules(*mat, i, j, dim);

            if (ans < 2 || ans > 3)
                new_mat[i][j] = false;
            if (ans == 3){
                
                new_mat[i][j] = true;
            }
                
        }
    }

    
    change = equal(*mat, new_mat, dim);

    matriscopy(*mat, new_mat);

    free(new_mat);

    return change;
}


/*
This is the main function in the case you want to execute the application without GUI.


int main(){

    bool ** mat;

    init_mat(&mat, DIM);

    start_cond(&mat);
    
    print_mat(mat, DIM);

    bool stop = false;

    while(!stop){
        fflush(stdin);
        getc(stdin);

        if (update(&mat, DIM))
            ;
            //stop = true;

        print_mat(mat, DIM);        
    }
    
    free(mat);

    return 0;
}

*/