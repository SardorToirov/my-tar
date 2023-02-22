#include "my_tar.h"

typedef struct variables{
    char* str;
    char* buffer;
    int count;
    int number;
    int sign;
    int ok;
}vars;

typedef struct my_tar_head{
	char a_name[100];
	char mode[8];
    char uid[8];
    char gid[8];
	char size[12];
    char mtime[12];
    char chksum[8];
    char typeflag;
    char linkname[100];
    char magic[6];
    char version[2];
    char uname[32];
    char gname[32];
    char devmajor[8];
    char devminor[8];
    char prefix[155];
    char padding[12];
} string_my_tar;

typedef struct {
    int name_size;
    int mode_size;
    int uid_size;
    int gid_size;
    int size_size;
    int mtime_size;
    int chksum_size;
    int linkname_size;
    int magic_size;
    int version_size;
    int uname_size;
    int gname_size;
    int devmajor_size;
    int devminor_size;
    int prefix_size;
    int padding_size;
} sizes;

sizes* set_sizes(string_my_tar* tar)
{
    sizes* res = (sizes*)malloc(sizeof(sizes) * 1);
    res->name_size = sizeof(tar->a_name);
    res->mode_size = sizeof(tar->mode);
    res->uid_size = sizeof(tar->uid);
    res->gid_size = sizeof(tar->gid);
    res->size_size = sizeof(tar->size);
    res->mtime_size = sizeof(tar->mtime);
    res->chksum_size = sizeof(tar->chksum);
    res->linkname_size = sizeof(tar->linkname);
    res->magic_size = sizeof(tar->magic);
    res->magic_size = sizeof(tar->version);
    res->version_size = sizeof(tar->version);
    res->uname_size = sizeof(tar->uname);
    res->gname_size = sizeof(tar->gname);
    res->devminor_size = sizeof(tar->devminor);
    res->devmajor_size = sizeof(tar->devmajor);
    return res;
}
void print_bufer(char* str){
    int i = 0;
    while(str[i]){
        write(1, &str[i], 1);
        i++;
    }
    write(1, "\n", 1);
}

void nulll(char* content, int size){
    int i = 0;
    while( i < size){
        content[i] = 0;
        i++;
    }
}

void list_to_null(char* content){
    int i = 0;
    while(content[i]){
        content[i] = 0;
        i++;
    }
}

int long_titude(char* c){
    vars* var = (vars*)malloc(sizeof(vars));
    var->count = 0;
    var->number = 0;
    while (c[var->number]){
        var->count+=c[var->number];
        var->number++;
    }
    return var->count;
}

int my_recursive_pow(int b, int e){
    if(e==0)
        return 1;
    else
        return (b*my_recursive_pow(b,e-1));

}

int my_atoi(char* str){
    vars* var = (vars*)malloc(sizeof(vars));
    var->count = 0;
    var->number = 1;
    int i = 0;
    if (str[0] == '-') {
        var->number = -1;
        i++;
    }
    for(;str[i] != '\0';){
        var->count = var->count * 10 + str[i] - '0';
        i++;
    }
        
    return var->number * var->count;
}

int my_converter_from_octal_to_decimal(char* str_num){
    vars* var = (vars*)malloc(sizeof(vars));
    var->count = my_atoi(str_num);
    var->number = 0;
    var->sign = 0;
    for(;var->count > 0;){
        var->ok = var->count % 10;
        var->count = var->count / 10;
        var->sign = var->sign + var->ok * my_recursive_pow( 8 , var->number );
        var->number++;
    }
    return var->sign;
}

int my_checksum(string_my_tar* text){
    vars* var = (vars*)malloc(sizeof(vars));
    var->count = 0;
    var->count += long_titude(text->a_name);
    var->count += long_titude(text->mode);
    var->count += long_titude(text->uid);
    var->count += long_titude(text->gid);
    var->count += long_titude(text->size);
    var->count += long_titude(text->mtime);
    var->count += long_titude(&text->typeflag);
    var->count += long_titude(text->magic);
    var->count += long_titude(text->uname);
    var->count += long_titude(text->gname);
    var->count += 256;
    return var->count;
}

char* to_octal(int num, int size){
    vars* var = (vars*)malloc(sizeof(vars));
    var->str = (char*)malloc(sizeof(char)* 20);
    var->buffer = (char*)malloc(sizeof(char)* 20);
    var->count = 0;
    var->number = 0;
    for(;num;){
        var->str[var->count++] = num % 8 + '0';
        num = num / 8;
    }
    for(;size;){
        if(var->count < size){
            var->buffer[var->number++]= '0';
            var->count++;
        }
        size--;
    }
    for(int i = strlen(var->str)-1; i >= 0; i--){
        var->buffer[var->number++] = var->str[i];
    }
    return var->buffer;
}

void start_fill_null(char* buff, int size)
{
    nulll(buff, size);
}

string_my_tar* my_file_zero(string_my_tar* tar){
    sizes* sizes_v = set_sizes(tar);
    start_fill_null(tar->a_name, sizes_v->name_size);
    start_fill_null(tar->mode, sizes_v->mode_size);
    start_fill_null(tar->uid, sizes_v->uid_size);
    start_fill_null(tar->gid, sizes_v->gid_size);
    start_fill_null(tar->size, sizes_v->size_size);
    start_fill_null(tar->mtime, sizes_v->mtime_size);
    start_fill_null(tar->chksum, sizes_v->chksum_size);
    tar->typeflag = 0;
    start_fill_null(tar->linkname, sizes_v->linkname_size);
    start_fill_null(tar->magic, sizes_v->magic_size);
    start_fill_null(tar->version, sizes_v->version_size);
    start_fill_null(tar->uname, sizes_v->uname_size);
    start_fill_null(tar->gname, sizes_v->gname_size);
    start_fill_null(tar->devmajor, sizes_v->devmajor_size);
    start_fill_null(tar->devminor, sizes_v->devminor_size);
    start_fill_null(tar->prefix, sizes_v->prefix_size);
    start_fill_null(tar->padding, sizes_v->padding_size);
    return tar;
}
int strcopy(char* dst, char* source)
{
    int i = 0;
    do {
        dst[i] = source[i];
        // i += 1;
    } while(source[i++]!='\0');
    return i;
}

void my_fill_tar(string_my_tar* fst, char* av){
    struct stat fs;
    stat(av, &fs);

    strcopy(fst->a_name, av);
    strcopy(fst->mode, to_octal(fs.st_mode, 7));
    strcopy(fst->uid, to_octal(fs.st_uid, 7));
    strcopy(fst->gid, to_octal(fs.st_gid, 7));
    strcopy(fst->size, to_octal(fs.st_size, 11));
    strcopy(fst->mtime, to_octal(fs.st_mtime, 11));
    strcopy(&fst->typeflag , "0");
    strcopy(fst->magic, "ustar  ");
    strcopy(fst->uname, "docode");
    strcopy(fst->gname, "docode");
    strcopy(fst->chksum, to_octal(my_checksum(fst), 6));
}

char* file(char* av){
    vars* var = (vars*)malloc(sizeof(vars));
    struct stat filestat;
    stat(av, &filestat);
    var->str = (char*)malloc(sizeof(char)*512);
    list_to_null(var->str);
    var->count = open(av, O_RDONLY);
    read(var->count, var->str, filestat.st_size);
    return var->str;
}

void print_my_archive_(char* fl){
    vars* var = (vars*)malloc(sizeof(vars));
    string_my_tar file_tar;
    var->count = open(fl, O_RDONLY);
    for(;read(var->count, &file_tar, 512) > 0;){
        if(strcmp(file_tar.magic, "ustar  ")==0){
            print_bufer(file_tar.a_name);
        }
    }
}

void overthrow_to(int ac, char** av){
    vars* var = (vars*)malloc(sizeof(vars));
    creat(av[2], 000644);
    struct stat fstat;
    int i = 3;
    while(i < ac){
        if(open(av[i], O_RDONLY) < 0){
            fprintf(stderr, "my_tar: %s: Cannot stat: No such file or directory\n", av[i]);
        }
        var->count = open(av[2],  O_WRONLY | O_APPEND );
        string_my_tar tar;
        my_file_zero(&tar);
        my_fill_tar(&tar, av[i]);
        write(var->count, &tar, 512);
        var->str = file(av[i]);
        write(var->count, var->str, 512);
        close(var->count);
        stat(av[i], &fstat);
        i++;
    }
}

void my_ower_file(char** av){
    vars* var = (vars*)malloc(sizeof(vars));
    string_my_tar len_tar;
    my_file_zero(&len_tar);
    my_fill_tar(&len_tar, av[3]);
    var->count = open(av[2], O_WRONLY | O_APPEND);
    write(var->count, &len_tar, 512);
    var->str = file(av[3]);
    write(var->count, var->str, 512); 
    close(var->count);
}

void tar_my_archive_(char* av){
    vars* var = (vars*)malloc(sizeof(vars));
    var->count = open(av, O_RDONLY);
    string_my_tar tar;
    for(;( read(var->count, &tar, 512) ) > 0;){
        if(strcmp(tar.magic, "ustar  ")==0){
            creat(tar.a_name, my_converter_from_octal_to_decimal(tar.mode));
            var->number = open(tar.a_name, O_WRONLY | O_APPEND);
            var->sign = my_converter_from_octal_to_decimal(tar.size);
            var->ok = 1;
            int file_size = var->sign;
            char* fl_content = (char*)malloc(sizeof(char)*var->sign);
            while(file_size > 0){
                read(var->count, fl_content, 1);
                write(var->number, fl_content, 1);
                file_size--;
            }
            close(var->number);
            var->ok *= 512;
            var->ok -= var->sign;
            lseek(var->count, var->ok, SEEK_CUR);
        }
    }
    close(var->count);
}

void check_un_tar(char** av){
    vars* var = (vars*)malloc(sizeof(vars));
    var->count = 3;
    var->number = 0;
    string_my_tar chesk_un;
    struct stat ft;
    var->ok = open(av[2], O_RDONLY);
    while ((read(var->ok, &chesk_un, 512)) > 0) {
        stat(av[var->count++], &ft);
        if(strcmp(chesk_un.a_name,  av[var->count]) ==0 && strcmp(chesk_un.magic,  "ustar  ") ==0 && strcmp(chesk_un.mtime, to_octal(ft.st_mtime, 12))==0){
            var->number++;
        }
    }
    close(var->ok);
}

void my_tar(int ac, char** av){
    char flag;
    for(int i = 1; i < ac; i++){
        if(strcmp(av[i], "-cf") == 0) flag = 'c';
        else if(strcmp(av[i], "-tf") == 0) flag = 't';
        else if(strcmp(av[i], "-uf") == 0) flag = 'u';
        else if(strcmp(av[i], "-rf") == 0) flag = 'r';
        else if(strcmp(av[i], "-xf") == 0) flag = 'x';
    }
    if(flag == 'c') overthrow_to(ac, av);
    else if(flag == 't') print_my_archive_(av[2]);
    else if(flag == 'r') my_ower_file(av);
    else if(flag == 'x') tar_my_archive_(av[2]);
    else if(flag == 'u') check_un_tar(av);
}

int main(int argc, char** argv){
    my_tar(argc, argv);
    return 0;
}

