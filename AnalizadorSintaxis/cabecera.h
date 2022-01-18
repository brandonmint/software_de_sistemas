typedef enum{
    PalRes, //0
    ID, //1
    NUM, //2
    SIM, //3
    OPAR, //4
    OPCOMP, //5
    OPASIGN, //6
    OPLOG, //7
    ESPECIAL, //8
    CAD, //8
    DESCONOCIDO //10
}TipoToken;

typedef enum{
    INT, //0
    STRING, //1
    CHAR, //2
    FLOAT, //3
    OTRO //4
}TipoDato;

typedef struct{
    TipoToken tipoToken;
    char lexema[100];
    TipoDato tipoDato;
}Token;

//Estructura del nodo
typedef struct nodo
{
    Token tok;
    struct nodo *siguiente;
    struct nodo *anterior;
} NODO;

NODO *CrearNodo(Token tok);
int InsertarInicio(NODO **cabeza, Token tok);
int InsertarFinal(NODO **cabeza,Token tok);
void ImprimirLista(NODO *cabeza);
