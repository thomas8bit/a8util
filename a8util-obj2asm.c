

#include <stdio.h>
#include <string.h>
 

FILE  *Source;

typedef struct {
    double x, y, z;
} coord_t;

coord_t vertex[100];

unsigned int vertex_num;

coord_t normal[100];

unsigned int normal_num;



void add_vertex(char *Buffer) {
    sscanf(Buffer, "%lf %lf %lf", &vertex[vertex_num].x, &vertex[vertex_num].y,
           &vertex[vertex_num].z);
    vertex_num++;
}

void add_normal(char *Buffer) {
    sscanf(Buffer, "%lf %lf %lf", &normal[normal_num].x, &normal[normal_num].y,
           &normal[normal_num].z);
    normal_num++;
}

void get_vtts_coord(coord_t *Array, int Index, int *PosX, int *PosY, int *PosZ) {
    *PosX = ((int)((double)256 * Array[Index].x)) & 0xffff;
    *PosY = ((int)((double)256 * Array[Index].y)) & 0xffff;
    *PosZ = ((int)((double)256 * Array[Index].z)) & 0xffff;
}

void add_surface(char *Buffer) {
    int vidx, nidx;
    int x, y, len, n;
    int posx, posy, posz;
    int add, draw;
    char stxt[0x1000];
    char first[0x100];

    x = 0;
    y = 0;
    add = 7;
    draw = 0;
    len = strlen(Buffer);
    do {
        n = sscanf(&Buffer[x], "%d//%d", &vidx, &nidx);
        if (n == 2) {
            vidx--;
            nidx--;
            add += 7;
            get_vtts_coord(vertex, vidx, &posx, &posy, &posz);
            y += sprintf(&stxt[y], "        .byte $%2.2X\n", draw);
            y += sprintf(&stxt[y], "        .word $%4.4X, $%4.4X, $%4.4X ; vtx %d\n",
                         posx, posy, posz, vidx + 1);
            if (draw == 0) {
                draw = 1;
                sprintf(first, "        .byte $01\n        .word $%4.4X, $%4.4X, $%4.4X ; vtx %d\n",
                        posx, posy, posz, vidx + 1);
                add += 7;
            }
            x++;
            while ((x < len) && (Buffer[x] != ' ')) {
                x++;
            }
        }
    } while ((x < len) && (n == 2));

    get_vtts_coord(normal, nidx, &posx, &posy, &posz);
    add |= 0x80;
    printf("        .byte $%2.2X\n", add);
    printf("        .word $%4.4X, $%4.4X, $%4.4X\n", posx, posy, posz);
    printf("%s", stxt);
    printf("%s", first);
}



char get_cmd(char *Cmd) {
    int x;
    char ret;

    ret = '#';
    x = strcmp(Cmd, "v");
    if (x == 0) {
        ret = 'V';
        goto leave;
    }
    x = strcmp(Cmd, "vn");
    if (x == 0) {
        ret = 'N';
        goto leave;
    }
    x = strcmp(Cmd, "f");
    if (x == 0) {
        ret = 'F';
        goto leave;
    }

 leave:
    return ret;
}

int main(int argc, char **argv) {
    unsigned int len, x;
    unsigned int result;
    char cmd;
    char line[100];
    char cmdbuf[100];


    Source = stdin;
    while (!feof(Source)) {
        fgets(line, sizeof(line), Source);
        if (!feof(Source)) {
            len = strlen(line);
            x = 0;
            do {
                cmdbuf[x] = line[x];
                x++;
            } while ((x < len) && (line[x] != ' '));
            cmdbuf[x] = 0;
            cmd = get_cmd(cmdbuf);
            switch (cmd) {
            case 'V':
                add_vertex(&line[x]);
                break;
            case 'N':
                add_normal(&line[x]);
                break;
            case 'F':
                add_surface(&line[x]);
                break;
            case '#':
            default:
                break;
            }
        }
    }
    printf("        .byte $80\n");
    printf("        .word $0000, $0000, $0000\n\n");
    return 0;
}

