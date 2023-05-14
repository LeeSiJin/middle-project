#include <iostream>
#include <fstream>
#include <string>

#include "p2.h"

using std::endl;
using std::ofstream;
using std::string;

class Board {
public:
    Board(int num_jobs, int width, int height, ofstream& output_stream);
    ~Board();

    void print_board();
    void print_job(int job_idx, char job_type, int id);

    // Job functions
    void insert_page(int x, int y, int width, int height, int id, char content);
    void delete_page(int id);
    void modify_content(int id, char content);
    void modify_position(int id, int x, int y);

private:
    int num_jobs, width, height;
    ofstream& output;
    char* board;
    Page** pages;

    Page* getPageById(int id);
};

Board::Board(int num_jobs, int width, int height, ofstream& output_stream) : output(output_stream) {
    this->num_jobs = num_jobs;
    this->width = width;
    this->height = height;

    board = new char[width * height];
    pages = new Page * [32766];

    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {
            board[h * width + w] = ' ';
        }
    }
}

Board::~Board() {
    delete[] board;
    delete[] pages;
}


Page* Board::getPageById(int id) {
    if (id>=0) {
        return pages[id];
    }
    return nullptr;
}

void Board::print_board() {
    int h, w;
    for (w = 0; w < width + 2; w++) {
        output << "- ";
    }
    output << endl;

    for (h = 0; h < height; h++) {
        output << "| ";
        for (w = 0; w < width; w++) {
            output << board[h * width + w] << " ";
        }
        output << "| " << endl;
    }

    for (w = 0; w < width + 2; w++) {
        output << "- ";
    }
    output << endl;
}

void Board::print_job(int job_idx, char job_type, int id) {
    output << ">> (" << job_idx << ") ";
    switch (job_type) {
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

void Board::insert_page(int x, int y, int width, int height, int id, char content) {
    if (x < 0 || x >= this->width || y < 0 || y >= this->height) {
        output << "Invalid position. Page cannot be inserted." << endl;
        return;
    }

    if (width <= 0 || height <= 0) {
        output << "Invalid dimensions. Page cannot be inserted." << endl;
        return;
    }

    Page* page = new Page(x, y, width, height, id, content);

    // Insert the page on the board
    for (int h = y; h < y + height; h++) {
        for (int w = x; w < x + width; w++) {
            if (h < this->height && w < this->width) {
                
                board[h * this->width + w] = content;
            }
        }
    }
    pages[id] = page;
    output << "Page inserted successfully." << endl;
    print_board();
}


void Board::delete_page(int id) {
    Page* page = getPageById(id);
    if (page == nullptr) {
        output << "Page with the given ID does not exist." << endl;
        return;
    }
    int currentX = page->getX();
    int currentY = page->getY();
    int width = page->getWidth();
    int height = page->getHeight();

    // Remove the pages in overlap relationship
    for (int h = currentY; h < currentY + height; h++) {
        for (int w = currentX; w < currentX + width; w++) {
            if (board[h * this->width + w] != ' ') {
                int currentPageId = getPageById(board[h * this->width + w])->getId();
                if (currentPageId != id) {
                    delete_page(currentPageId);
                }
            }
        }
    }

    // Remove the target page
    for (int h = currentY; h < currentY + height; h++) {
        for (int w = currentX; w < currentX + width; w++) {
            board[h * this->width + w] = ' ';
            pages[h * this->width + w] = nullptr;
        }
    }

    // Put the pages removed from above back on in reversed order
    for (int h = currentY - 1; h >= 0; h--) {
        for (int w = currentX; w < currentX + width; w++) {
            if (board[h * this->width + w] != ' ') {
                int removePageId = getPageById(board[h * this->width + w])->getId();
                char removePageContent = getPageById(board[h * this->width + w])->getContent();
                delete_page(removePageId);
                insert_page(currentX, currentY, width, height, removePageId, removePageContent);
            }
        }
    }

    output << "Page deleted successfully." << endl;
    print_board();
}




void Board::modify_content(int id, char content) {
    Page* page = getPageById(id);
    if (page == nullptr) {
        output << "Page with the given ID does not exist." << endl;
        return;
    }
    int currentX = page->getX();
    int currentY = page->getY();
    int width = page->getWidth();
    int height = page->getHeight();

    // Remove the pages in overlap relationship
    for (int h = currentY; h < currentY + height; h++) {
        for (int w = currentX; w < currentX + width; w++) {
            if (board[h * this->width + w] != ' ') {
                int currentPageId = getPageById(board[h * this->width + w])->getId();
                if (currentPageId != id) {
                    delete_page(currentPageId);
                }
            }
        }
    }

    // Modify the target page
    for (int h = currentY; h < currentY + height; h++) {
        for (int w = currentX; w < currentX + width; w++) {
            pages[h * this->width + w]->setContent(content);
        }
    }

    // Put the pages removed from above back on in reversed order
    for (int h = currentY - 1; h >= 0; h--) {
        for (int w = currentX; w < currentX + width; w++) {
            if (board[h * this->width + w] != ' ') {
                int removePageId = getPageById(board[h * this->width + w])->getId();
                char removePageContent = getPageById(board[h * this->width + w])->getContent();
                delete_page(removePageId);
                insert_page(currentX, currentY, width, height, removePageId, removePageContent);
            }
        }
    }

    output << "Page content modified successfully." << endl;
    print_board();
}

void Board::modify_position(int id, int x, int y) {
    Page* page = getPageById(id);
    if (page == nullptr) {
        output << "Page with the given ID does not exist." << endl;
        return;
    }


    int currentX = page->getX();
    int currentY = page->getY();
    int width = page->getWidth();
    int height = page->getHeight();
    char content = page->getContent();

    // Remove the pages above the target page
    for (int h = currentY - 1; h >= 0; h--) {
        for (int w = currentX; w < currentX + width; w++) {
            if (pages[h * this->width + w] != nullptr) {
                int removePageId = pages[h * this->width + w]->getId();
                delete_page(removePageId);
            }
        }
    }

    // Remove the target page
    for (int h = currentY; h < currentY + height; h++) {
        for (int w = currentX; w < currentX + width; w++) {
            board[h * this->width + w] = ' ';
            pages[h * this->width + w] = nullptr;
        }
    }

    // Put the page back on the board at the new position
    insert_page(x, y, width, height, id, content);

    // Put the pages removed from above back on in reversed order
    for (int h = currentY - 1; h >= 0; h--) {
        for (int w = currentX; w < currentX + width; w++) {
            if (pages[h * this->width + w] != nullptr) {
                int removePageId = pages[h * this->width + w]->getId();
                char removePageContent = pages[h * this->width + w]->getContent();
                delete_page(removePageId);
                insert_page(currentX, currentY, width, height, removePageId, removePageContent);
            }
        }
    }

    output << "Page position modified successfully." << endl;
    print_board();
}




