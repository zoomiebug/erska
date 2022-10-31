typedef int     gwthd_t;
typedef void *(*gwthd_fn_t)(void *);

int     gwthd_create(gwthd_t *childid, gwthd_fn_t fn, void *data);
void    gwthd_exit(void);
int     gwthd_join(gwthd_t child);
gwthd_t gwthd_id(void);

/* Supported function */
int clone(gwthd_fn_t fn, void *arg, void *stack);
int join(void** stack, gwthd_t childid);
int get_gwthd_id(gwthd_t * id);

/* extra credits */
void gwthd_exit2(void *data);
int  gwthd_join2(gwthd_t child, void **data);