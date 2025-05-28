struct LN{
    char* text;
    struct LN* next;
}typedef LineNode;

LineNode* init_LN(const char* text);
int free_node(LineNode* head);

int add(LineNode* head, int line_num, char* text);
int append(LineNode* head, char* text);
int drop(LineNode* head, int start, int stop);
int edit(LineNode* head, int line_num, char* text);

int print_lines(LineNode* head, int start, int stop);
int print_all(LineNode* head);
int length(LineNode* head);