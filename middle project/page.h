using namespace std;
#include <vector>

class Page {
    public:
        Page();
        Page(int X, int Y, int Width, int Height, int Id, int Content);
        void input_conflict_page(int i);
        int getReturnX() { return x; }
        int getreturny() { return y; }
        int getreturnwidth() { return width; }
        int getreturnheight() { return height; }
        int getreturnid() { return id; }
        char getreturncontent() { return content; }
        int getreturnconflict_page(int i) { return conflict_page[i]; }
        int getCPsize() { return conflict_page.size(); }
        vector<int> get_conflictpage() { return conflict_page; }
        void setcontent(char cont) { content = cont; }
        void setx(int newx) { x = newx; }
        void sety(int newy) { y = newy; }
        


    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id; // unique id for each page
        char content; 
        vector<int> conflict_page;
};
 Page::Page() {
    x = 0;
    y = 0;
    id = 0;
    width = 0;
    height = 0;
    content = ' ';
   
}

void Page::input_conflict_page(int i) {
    conflict_page.push_back(i);
}



Page::Page(int X, int Y, int Width, int Height, int Id, int Content) {
    x = X;
    y = Y;
    id = Id;
    width = Width;
    height = Height;
    content = Content;
    /*
    for (int i = 0; i < 32767; i++)
    {
        conflict_page[i] = false;
    }*/
}
