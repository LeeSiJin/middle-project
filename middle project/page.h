class Page {
    public:
        Page{int X, int Y, int Width, int Height, int Id, char Content}:x(X),y(Y),width(Width),height(Height),id(Id),content(Content)
        {}
    private:
        int x, y; // position of the page on the board
        int width, height; // width and height of the page 
        int id; // unique id for each page
        char content; 
};

