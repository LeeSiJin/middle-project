using namespace std;

class Page {
    public:
        Page(int X, int Y, int Width, int Height, int Id, int Content);
        void input_conflict_page(int i);
        int getreturnx() { return x; }
        int getreturny() { return y; }
        int getreturnwidth() { return width; }
        int getreturnheight() { return height; }
        int getreturnid() { return id; }
        char getreturnchar() { return content; }
        bool getreturnconflict_page(int i) { return conflict_page[i]; }
        
    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id; // unique id for each page
        char content; 
        bool conflict_page[32767];
};

void Page::input_conflict_page(int i) {
    conflict_page[i] = true;
}



Page::Page(int X, int Y, int Width, int Height, int Id, int Content) {
    x = X;
    y = Y;
    id = Id;
    width = Width;
    height = Height;
    content = Content;
    
    for (int i = 0; i < 32767; i++)
    {
        conflict_page[i] = false;
    }
}
