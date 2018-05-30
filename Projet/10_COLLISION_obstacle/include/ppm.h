int wi,ha;

/* Infos sur le header du fichier -> Nombre magique (P3)
et hauteur, largeur, valeur max de couleur (255)*/
typedef struct header {
    char format[2]; /* P1, P2, P3... (magic number) */
    int width;
    int height;
    int max_color;
} Header;

unsigned char next_char(FILE * f);
unsigned int next_int(FILE * f);
Header get_header(FILE * f);
void print_header(Header head);
void drawRepere();
void drawRect(int R, int V, int B);
void drawLevel(int level[wi][ha][3]);
int createTab(int levelarray[wi][ha][3],char *filename);
