using namespace std;

class Page {
    public:
        Page(int X, int Y, int Width, int Height, int Id, int Content);
    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id; // unique id for each page
        char content; 
};

Page::Page(int X, int Y, int Width, int Height, int Id, int Content) {
    x = X+1;
    y = Y+1;
    width = Width;
    height = Height;
    content = Content;
    for (int i = x; i <= x+width; i++)
    {
        for (int j = y; j <= y + height; y++) {
            cout << content;
        }
        cout << endl;
    }
}