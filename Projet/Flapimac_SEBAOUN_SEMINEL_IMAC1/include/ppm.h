int w,h;


typedef struct header {
    char format[2]; /* P1, P2, P3... (magic number) */
    int width;
    int height;
    int max_color;
} Header;


typedef struct pixel {
    unsigned int R, V, B;
} Pixel;


typedef struct image {
    Header header;
    Pixel* pixels;
} Image;

unsigned char next_char(FILE * f);
unsigned int next_int(FILE * f);
Header get_header(FILE * f);
void print_header(Header head);
void reshape();
void setVideoMode();
void drawRepere();
void drawRect(int R, int V, int B);

int createTab(int levelarray[w][h][3],char *filename);
  /* Read the ppm file : filename and create an array who save every pixel from the file in a case */
