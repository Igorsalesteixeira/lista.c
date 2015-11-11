#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CLIENTS 10
#define MAX_NPC 100

struct npc {
	char name[20];
	char class[20];
	int hp;
	int strength;
	int mana;
	int magic;
	int luck;
	int level;
};

struct player {
	char name[20];
	char class[10];
	int hp;
	int strength;
	int mana;
	int magic;
	int luck;
	int exp;
	int level;	
};

void char_record(struct player *, int n); 
void npc_record(struct npc *, int np);
void list_char(struct player *, int n);
void list_npc(struct npc *, int np);
void select_char(struct player *, int n, int *selectp);
void select_enemy(struct npc *, int np, int *selectm);
int delete_char(struct player *, int n); 
int delete_npc(struct npc*, int np);
int menu_select(void); 
int class_select(void);
void battle(struct player *, struct npc *, int selectp, int selectm);

void main(void)
{
	int choice, n=0, np=0, selectp, selectm;

	struct player clients[MAX_CLIENTS];
	struct npc monster[MAX_NPC];

	for(;;) {
		choice=menu_select();
		switch(choice) {
				case 1: system("clear");
				select_char(clients, n, &selectp);
				select_enemy(monster, np, &selectm);
				battle(clients, monster, selectp, selectm);	
				break;
			case 2: if(n < MAX_CLIENTS) {
					char_record(clients, n);
					n++;
				} else {
					printf("\nVocê atingiu o limite de personagens!\n\n");
				}
				break;
			case 3: list_char(clients, n);
				break;
			case 4: delete_char(clients, n);
				break;
			case 5: if (np < MAX_NPC) {
					npc_record(monster, np);
					np++;	
				} else {
					printf("\n VocÊ atingiu o limite de npcs!\n\n");
				}
				break;
			case 6: list_npc(monster, np);
				break;
			case 7: delete_npc(monster, np);
				break;
			case 8: exit(0);
		}
	}
}

int menu_select(void)
{
	char s[80];
	int o;

	printf("\n1. Start\n"); 
	printf("2. Inserir um char\n");
	printf("3. Lista de char\n");
	printf("4. Deletar char\n");
	printf("5. inserir um npc\n");
	printf("6. Lista de npc\n");
	printf("7. Deletar um npc\n");
	printf("8. Sair\n");
	do {
		printf("\nDigite sua escolha: ");
			fgets(s, sizeof(s), stdin);
		o = atoi(s);	
	} while(o<0 || o>8);
	return o;
}

int class_select(void)
{
	char o[20];
	int c;
		printf("\n1. para guerreiro\n");
		printf("2. para mago\n");
		printf("3. para arqueiro\n");
		do {
			printf("\nDigite sua raça: ");
			fgets(o, sizeof(o), stdin);
			c = atoi(o);
		}	while(c<0 || c>3);
				return c;				
}

void initialize_npc(struct npc *m)
{
	char class[20];
	int hp;
	int mana;
	int strength;
	int magic;
	int luck;
	int level;

	printf("Digite a classe do npc: ");
	fgets(class, sizeof(class), stdin);
	strcpy(m->class, class);
	printf("Digite o hp do npc: ");
	scanf ("%d", &hp);
	m->hp = hp;
	printf("Digite a mana do npc: ");
	scanf("%d", &mana);
	m->mana = mana;
	printf("Digite a força do npc: ");
	scanf("%d", &strength);
	m->strength = strength;
	printf("Digite a magia do npc: ");
	scanf("%d", &magic);
	m->magic = magic;
	printf("Digite a sorte do npc: ");
	scanf("%d", &luck);
	m->luck = luck;
	printf("Digite o level do npc: ");
	scanf("%d", &level);
	m->level = level;	
}

void initialize(struct player *l, int c	) {

	switch(c) {
		case 1: // Fighter
			strcpy(l->class, "Warrior");
			l->hp = 100;
			l->mana = 50;
			l->strength = 150;
			l->magic = 50;
			l->luck = 50;
			l->exp = 1;
			l->level = 1;
			break;
		case 2: // Mage
			strcpy(l->class, "Mage");
			l->hp = 100;
			l->mana = 50;
			l->strength = 50;
			l->magic = 150;
			l->luck = 50;
			l->exp = 1;
			l->level = 1;
			break;
		case 3: // Archer
			strcpy(l->class, "Archer");
			l->hp = 100;
			l->mana = 50;
			l->strength = 100;
			l->magic = 50;
			l->luck = 100;
			l->exp = 1;
			l->level = 1;
			break;
	}
}	

void char_record(struct player clients[], int n)
{
	struct player *l;
	l = (struct player *)malloc(sizeof(struct player));
	if (!l) {
		printf("Não conseguiu alocar a memória.\n");
		exit(1);
	}

	printf("Digite o nome: ");
	fgets(l->name, sizeof(l->name), stdin);

	int c = class_select();
	initialize(l, c);

	clients[n] = *l;
	free(l);
}

void npc_record(struct npc monster[], int np)
{
	struct npc *m;
	m = (struct npc *)malloc(sizeof(struct npc));
	if (!m) {
		printf("Não conseguiu alocar a memória.\n");
		exit(1);
	}
	
	printf("Digite o nome: ");
	fgets(m->name, sizeof(m->name), stdin);

	initialize_npc(m);

	monster[np] = *m;
	free(m);
}

int delete_char(struct player clients[], int n)
{
	char o[10];
	int c;
		for(int i=0; i<n; i++) {
			printf("\nPersonagem %d: %s", i, clients[i].name);
		}
		printf("\nDigite o numero do personagem a ser deletado\n");
		fgets(o, sizeof(o), stdin);
		c = atoi(o);
		if(c>=0 && c<=n)
			printf("\nPersonagem %s:deletado com sucesso!\n", clients[c].name);
			clients[c].name[0] = '\0';
			clients[c].class[0] = '\0';
			clients[c].hp = '\0';
			clients[c].mana = '\0';
			clients[c].strength = '\0';
			clients[c].magic = '\0';
			clients[c].luck = '\0';
			clients[c].exp = '\0';
			clients[c].level = '\0';
}

int delete_npc(struct npc monster[], int np)
{
	char o[10];
	int c;
		for(int i=0; i<np; i++) {
			printf("\nPersonagem %d: %s", i, monster[i].name);
		}
		printf("\n Digite o numero do NPC a ser deletado\n");
		fgets(o, sizeof(o), stdin);
		c = atoi(o);
		if(c>=0 && c<=np)
			printf("\nNpc %s:deletado com sucesso!\n", monster[c].name);
			monster[c].name[0] = '\0';
			monster[c].class[0] = '\0';
			monster[c].hp = '\0';
			monster[c].mana = '\0';
			monster[c].strength = '\0';
			monster[c].magic = '\0';
			monster[c].luck = '\0';
			monster[c].level = '\0';			
}

void list_char(struct player clients[], int n)
{
	for(int i=0;i<n;i++){
		printf("CHAR: %s\n", clients[i].name);
		printf("CLASS = %s\n", clients[i].class);
		printf("HP = %d\n", clients[i].hp);
		printf("MANA = %d\n", clients[i].mana);
		printf("STRENGTH = %d\n", clients[i].strength);
		printf("MAGIC = %d\n", clients[i].magic);
		printf("LUCK = %d\n", clients[i].luck);
		printf("EXP = %d\n", clients[i].exp);
		printf("LEVEL = %d\n", clients[i].level);
		printf("\n\n");
	}
};

void list_npc(struct npc monster[], int np)
{
	for(int i=0; i<np; i++){
		printf("Npc =  %s\n", monster[i].name);
		printf("Class = %s\n", monster[i].class);
		printf("Hp = %d\n", monster[i].hp);
		printf("Mana = %d\n", monster[i].mana);
		printf("Strength = %d\n", monster[i].strength);
		printf("Magic = %d\n", monster[i].magic);
		printf("Luck = %d\n", monster[i].luck);
		printf("Level = %d\n", monster[i].level);
		printf("\n\n");
	}
}

void select_char(struct player clients[], int n, int *selectp)
{
	int i;
	printf("\nDigite o numero do personagem que deseja usar\n\n");
	for(i=0;i<n;i++){
                printf("Personagem %d: %s\n", i, clients[i].name);
	}
	scanf("%d", selectp);	
	printf("\nO personagem escolhido foi o %s\n", clients[*selectp].name);
}

void select_enemy(struct npc monster[], int np, int *selectm)
{
	int i;
	printf("\nDigite o numero do NPC que deseja lutar\n\n");
	for(int i=0; i<np; i++){
		printf("Npc %d: %s\n", i, monster[i].name);
	}	
	scanf("%d", selectm);
	printf("\nO Npc escolhido foi o %s\n", monster[*selectm].name);
}

void battle(struct player clients[], struct npc monster[], int choicep, int choicem)
{
	int a;
	printf("\nA batalha vai começar!\n");
	do {
		printf("\nDigite 1 para atacar e 2 para fugir da luta\n");
		scanf("%d", &a);
			if(a=1){
				monster[choicem].hp = monster[choicem].hp -20;
				printf("Você causou 20 de dano no seu oponente e restou %d\n", monster[choicem].hp);
				clients[choicep].hp = clients[choicep].hp - 50;
				printf("Você recebeu 50 de dano do seu oponente e restou %d\n", clients[choicep].hp);
			} else {
				printf("Você fugiu da luta\n");
			}
	} while(clients[choicep].hp>0);
	printf("%s foi derrotado por %s!\n", clients[choicep].name, monster[choicem].name);
}
