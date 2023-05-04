#include <fstream>

#include "page.h"

using std::endl;
using std::ofstream;

class Board {
    public:
        Board(int num_jobs, int width, int height, ofstream& output_stream);
        ~Board();

        void print_board();
        void print_job(int job_idx, char job_type, int id);

        //job functions
        void insert_page(int x, int y, int width, int height, int id, int content);
        void delete_page(int id);
        void modify_content(int id, char content);
        void modify_position(int id, int x, int y);

    private:
        int num_jobs, width, height; 
        ofstream& output; 
        char* board; 
};


Board::Board(int num_jobs, int width, int height, ofstream& output_stream): output(output_stream) {
    this->width = width;
    this->height = height;
    this->num_jobs = num_jobs;

    board = new char[width*height];

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h*width + w] = ' ';
        }
    }

}

Board::~Board() {
    delete board;
    
}


void Board::print_board() {
    int h, w;
    for (w = 0; w < width+2; w++) output << "- ";
    output << endl;
    
    for (h = 0; h < height; h++) {
        output << "| ";
        for (w = 0; w < width; w++) {
            output << board[h*width + w] << " ";
        }
        output << "| " << endl;
    }

    for (w = 0; w < width+2; w++) output << "- ";
    output << endl;
}

void Board::print_job(int job_idx, char job_type, int id) {
    output << ">> (" << job_idx <<") ";
    switch(job_type) {
        
        case 'i':
            output << "Insert ";
            break;
        case 'd':
            output << "Delete ";
            break;
        case 'm':
            output << "Modify ";
            break;
    }

    output << id << endl;
}

bool check_conflict(int x, int y, int z, int k, int a, int b, int c, int d) {
    int leftup_a[2] = { y, x };
    int rightup_a[2] = { y,x+z };
    int leftdown_a[2] = { y+k,x};
    int rightdown_a[2] = { y+k,x+z };

    int leftup_b[2] = { b,a };
    int rightup_b[2] = { b, a+c};
    int leftdown_b[2] = { b+d, a };
    int rightdown_b[2] = { b+d,a+c };

    //or 어떻게
    if (a + c<x ll a>x + z ll b > y + k ll b + d < y) {
        return true;
    }

}

//page 저장할 page array
Page page_array[32767];
int page_counter = 0;

void Board::insert_page(int x, int y, int width, int height, int id, int content) {
    Page newpage(x, y, width, height, id, content); //page만들기    
    
    //충돌이 난 경우 conflict page에 기록
    for (int i = 0; i < page_counter; i++)
    {
        // check 함수를 통해 겹치는 지 확인
        check_conflict(page_array[i].getreturnx(), page_array[i].getreturny(), page_array[i].getreturnwidth(), page_array[i].getreturnheight(), x, y, width, height);
        // 겹치는 결과 반영
        newpage.input_conflict_page(i);
    }

    //보드에 내용 넣어주기
    for (int i = y; i < y+width; i++)
    {
        for (int k = x; k < x+height; k++)
        {
            //이거 포인터로 어떻게?
            board[i][k] = content;
        }
    }
   
    page_array[page_counter++] = newpage;
}

void Board::delete_page(int id) {
    
    
}

void Board::modify_content(int id, char content) {
   

}
void Board::modify_position(int id, int x, int y) {
   
    
}

