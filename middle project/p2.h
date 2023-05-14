class Page {
public:
    // Constructor
    Page(int x, int y, int width, int height, int id, char content);

    // Getter methods
    int getX() const;
    int getY() const;
    int getWidth() const;
    int getHeight() const;
    int getId() const;
    char getContent() const;

    // Setter methods
    void setX(int x);
    void setY(int y);
    void setWidth(int width);
    void setHeight(int height);
    void setId(int id);
    void setContent(char content);

private:
    int x, y; // position of the page on the board
    int width, height; // width and height of the page 
    int id; // unique id for each page
    char content; 
};

// Constructor implementation
Page::Page(int x, int y, int width, int height, int id, char content)
    : x(x), y(y), width(width), height(height), id(id), content(content) {
}

// Getter methods implementation
int Page::getX() const {
    return x;
}

int Page::getY() const {
    return y;
}

int Page::getWidth() const {
    return width;
}

int Page::getHeight() const {
    return height;
}

int Page::getId() const {
    return id;
}

char Page::getContent() const {
    return content;
}

// Setter methods implementation
void Page::setX(int x) {
    this->x = x;
}

void Page::setY(int y) {
    this->y = y;
}

void Page::setWidth(int width) {
    this->width = width;
}

void Page::setHeight(int height) {
    this->height = height;
}

void Page::setId(int id) {
    this->id = id;
}

void Page::setContent(char content) {
    this->content = content;
}
