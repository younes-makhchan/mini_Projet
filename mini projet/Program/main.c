#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void clearfile(int choice){
    FILE *fp;
    if(choice==1)
        fp=fopen("voiture.txt","w");
    else if(choice==2)
        fp=fopen("client.txt","w");
    else if(choice==3)
        fp=fopen("contrat.txt","w");
    fprintf(fp,"");
    fclose(fp);
}
typedef struct date{
int jj,mm,an;
}Date;
typedef struct voiture{
    int idVoiture;
    char marque[15];
    char nomVoiture[15];
    char couleur[7];
    int nbplaces;
    int prixJour;
    char EnLocation[4];
} Voiture;
void voitureSendData(Voiture v){
    FILE *fp=fopen("voiture.txt","a");
    int i=0;
    fprintf(fp,"%d %s %s %s %d %d %s\n",v.idVoiture,v.marque,v.nomVoiture,v.couleur,v.nbplaces,v.prixJour,v.EnLocation);
    fclose(fp);
}
Voiture *voitureFetchData(int *length){
    FILE *fp=fopen("voiture.txt","a+");
    int size=0;
    char c;
    while(!feof(fp)){
        c=getc(fp);
        if(c=='\n'){
            size++;}
    }
    *length=size;
    if(size==0){
        fclose(fp);
    return NULL;
    }
    Voiture *tab=(Voiture*)malloc(sizeof(Voiture)*size);
    int i=0;
    fseek(fp,0,SEEK_SET);
    while(!feof(fp)){
        fscanf(fp,"%d %s %s %s %d %d %s\n",&(tab+i)->idVoiture,(tab+i)->marque,(tab+i)->nomVoiture,(tab+i)->couleur,&(tab+i)->nbplaces,&(tab+i)->prixJour,(tab+i)->EnLocation);
        i++;
    }
    fclose(fp);
    return tab;
};
int rechercheVoiture(Voiture *voitures,int size,int ID){int i;
    for(i=0;i<size;i++){
        if(voitures[i].idVoiture==ID){
            return 1;
        }
    }
    return 0;
}
typedef struct Contractlocation{
    float numContrat;
    int idVoiture;
    int idClient;
    Date debut;
    Date fin;
    int cout;
}Contrat;
void contratSendData(Contrat contrat){
    FILE * fp=fopen("contrat.txt","a");
    int i=0;
    fprintf(fp,"%f %d %d %d %d %d %d %d %d %d\n",(contrat).numContrat,(contrat).idVoiture,(contrat).idClient,contrat.debut.jj,contrat.debut.mm,contrat.debut.an,contrat.fin.jj,contrat.fin.mm,contrat.fin.an,contrat.cout);
    fclose(fp);
}
Contrat *contratFetchData(int *length){
    FILE * fp=fopen("contrat.txt","a+");
    int size=0,i=0;;
    char c;
    while(!feof(fp)){
        c=getc(fp);
        if(c=='\n'){
            size++;}
    }
    *length=size;
    if(size==0){
        fclose(fp);
        return NULL;
    }
    Contrat *contrat=(Contrat*)malloc(sizeof(Contrat)*size);
    fseek(fp,0,SEEK_SET);
    while(!feof(fp)){
        fscanf(fp,"%f %d %d %d %d %d %d %d %d %d\n",&(contrat+i)->numContrat,&(contrat+i)->idVoiture,&(contrat+i)->idClient,&(contrat+i)->debut.jj,&(contrat+i)->debut.mm,&(contrat+i)->debut.an,&(contrat+i)->fin.jj,&(contrat+i)->fin.mm,&(contrat+i)->fin.an,&(contrat+i)->cout);
        i++;
    }
    fclose(fp);
    return contrat;
};
int rechercheContrat(Contrat *contrat,int size,float num){
    int i;
    for(i=0;i<size;i++){
        if((contrat+i)->numContrat==num)
            return 1;
    }
    return 0;
}
typedef struct client{
    int idClient;
    char nom[20];
    char prenom[20];
    int cin;
    char adresse[15];
    int telephone;
}Client;
void clientSendData(Client client){
    FILE * fp=fopen("client.txt","a+");
    int i=0;
    fprintf(fp,"%d %s %s %d %s %d\n",client.idClient,client.nom,client.prenom,client.cin,client.adresse,client.telephone);
    fclose(fp);
}
Client *clientFetchData(int*length){
    FILE * fp=fopen("client.txt","a+");
    int size=0,i=0;;
    char c=getc(fp);
    while(c!=EOF){
        if(c=='\n')
            size++;
        c=getc(fp);
    }
    *length=size;
    if(size==0){
        fclose(fp);
        return NULL;
    }
    Client *client=(Client*)malloc(sizeof(Client)*size);
    fseek(fp,0,SEEK_SET);
    while(!feof(fp)){
        fscanf(fp,"%d %s %s %d %s %d\n",&(client+i)->idClient,(client+i)->nom,(client+i)->prenom,&(client+i)->cin,(client+i)->adresse,&(client+i)->telephone);
        i++;
    }
    fclose(fp);
    return client;
};
int rechercheClient(Client *client,int size,int ID){
    int i;
    printf("%d",size);
    for(i=0;i<size;i++){
        if((client+i)->idClient==ID)
            return 1;
    }
    return 0;
}
int Calculcout(Date debut,Date fin){
    int start=debut.jj+debut.mm*30+debut.an*365;
    int finish=fin.jj+fin.mm*30+fin.an*365;
    return start-finish;
 }
void quitter(){
printf("QUITTER");};
void erreur(){
printf("ERREUR");};

//voiture functions
void Liste_voiture(){
    int size,i;
    Voiture *voiture=voitureFetchData(&size);
    if(voiture==NULL){
        printf(" \n\t\tPas de voiture pour afficher\n");
    }
    else{
        for(i=0;i<size;i++){
            printf(" \n\t\t1) IDvoiture      : %d\n \t\t2) Marque         : %s\n \t\t3) Nom de voiture : %s\n \t\t4) Couleur        : %s\n \t\t5) Nombre places  : %d\n \t\t6) Prix de jour   : %d\n \t\t7) enLocation     : %s\n",(voiture+i)->idVoiture,(voiture+i)->marque,(voiture+i)->nomVoiture,(voiture+i)->couleur,(voiture+i)->nbplaces,(voiture+i)->prixJour,(voiture+i)->EnLocation);
        }
    };
    free(voiture);
}
void Ajouter_voiture(){
    int i,size;
    Voiture *voiture,*voitures=voitureFetchData(&size);
    voiture=(Voiture*)malloc(sizeof(Voiture));
    printf("\n\n\t\t1) Donner votre  voiture ID           :\t");
    scanf("%d",&voiture->idVoiture);
    if(rechercheVoiture(voitures,size,voiture->idVoiture)){
        printf(" \t\tSe ID est deja dans  le systeme\n");
        printf(" \t\tClick un nombre pour retourner : ");
        scanf("%d",&i);
        free(voitures);
        printf("\n");
        Ajouter_voiture();
    }
    printf("\t\t2) Donner votre  voiture marque       :\t");
    scanf("%s",voiture->marque);
    printf("\t\t3) Donner votre  voiture nom          :\t");
    scanf("%s",voiture->nomVoiture);
    printf("\t\t4) Donner votre  voiture color        :\t");
    scanf("%s",voiture->couleur);
    printf("\t\t5) Donner votre  voiture nomber place :\t");
    scanf("%d",&voiture->nbplaces);
    printf("\t\t6) Donner votre  voiture prix de jour :\t");
    scanf("%d",&voiture->prixJour);
    printf("\t\t7) Votre voiture en location est      :\t");
    scanf("%s",voiture->EnLocation);
    voitureSendData(*voiture);
    menuGV();
    return 0;
}
void Modifier_voiture(){
    int i,size,ID;
    Liste_voiture();
    printf(" \n\t\tDonner la voiture ID : ");
    scanf("%d",&ID);
    Voiture *voiture=voitureFetchData(&size);
    if(!rechercheVoiture(voiture,size,ID)){
        printf(" \t\tIl n'y a pas cet ID\n");
        printf(" \t\tClick un nombre pour retourner : ");
        scanf("%d",&i);
        printf("\n");
        Modifier_voiture();
    };
    clearfile(1);
    for(i=0;i<size;i++){
        if(ID==voiture[i].idVoiture){
            printf("\t\t1) Donner votre  voiture ID           :\t");
            scanf("%d",&voiture[i].idVoiture);
            printf("\t\t2) Donner votre  voiture marque       :\t");
            scanf("%s",voiture[i].marque);
            printf("\t\t3) Donner votre  voiture nom          :\t");
            scanf("%s",voiture[i].nomVoiture);
            printf("\t\t4) Donner votre  voiture color        :\t");
            scanf("%s",voiture[i].couleur);
            printf("\t\t5) Donner votre  voiture nomber place :\t");
            scanf("%d",&voiture[i].nbplaces);
            printf("\t\t6) Donner votre  voiture prix de jour :\t");
            scanf("%d",&voiture[i].prixJour);
            printf("\t\t7) Votre voiture en location est      :\t");
            scanf("%s",voiture[i].EnLocation);
        }
        voitureSendData(voiture[i]);
    }
    free(voiture);
    menuGV();
}
void Supprimer_voiture(){
    Liste_voiture();
    int ID,size=0,i;
    //fscanf u should put all the variables all the line get it
    printf(" \n\t\tDonner la voiture ID : ");
    scanf("%d",&ID);
    Voiture *voiture=voitureFetchData(&size);
    if(!rechercheVoiture(voiture,size,ID)){
        printf(" \t\tIl n'y a pas cet ID\n");
        printf(" \t\tClick un nombre pour retourner : ");
        scanf("%d",&i);
        printf("\n");
        Supprimer_voiture();
    };
    clearfile(1);
    for(i=0;i<size;i++){
        if(voiture[i].idVoiture!=ID){
            voitureSendData(voiture[i]);
        }
    }
    free(voiture);
    menuGV();
}

//Client function
void Liste_client(){
    int size,i;
    Client *client=clientFetchData(&size);
    //!feof(fpoinet ) easy way
    if(client==NULL){
        printf(" \n\t\tPas de client pour afficher\n");
    }
    else{
        for(i=0;i<size;i++){
            printf(" \n\t\t1) IDclient  : %d\n \t\t2) Nom       : %s\n \t\t3) Prenom    : %s\n \t\t4) Cin       : %d\n \t\t5) Adresse   : %s\n \t\t6) Telephone : %d\n",(client+i)->idClient,(client+i)->nom,(client+i)->prenom,(client+i)->cin,(client+i)->adresse,(client+i)->telephone);
        }
    }
    free(client);
}
void Ajoute_client(){
    int size,i;
    Client client ,*clients=clientFetchData(&size);
    printf("\n\n\t\t1) Donner votre  client ID          :\t");
    scanf("%d",&client.idClient);
    if(rechercheClient(clients,size,client.idClient)){
        printf(" \t\tSe ID est deja dans  le systeme\n");
        printf(" \t\tClick un nombre pour retourner : ");
        scanf("%d",&i);
        printf("\n");
        Ajoute_client();
    }
    printf("\t\t2) Donner votre  client nom         :\t");
    scanf("%s",client.nom);
    printf("\t\t3) Donner votre  client prenom      :\t");
    scanf("%s",client.prenom);
    printf("\t\t4) Donner votre  client cin         :\t");
    scanf("%d",&client.cin);
    printf("\t\t5) Donner votre  client adresse     :\t");
    fflush(stdin);
    gets(client.adresse);
    printf("\t\t6) Donner votre  client telephone   :\t");
    scanf("%d",&client.telephone);
    clientSendData(client);
    menuGC();
    return 0;
}
void Modifier_client(){
    int size,i;
    Client *client=clientFetchData(&size);
    Liste_client();
    int ID;
    //fscanf u should put all the variables all the line get it
    printf(" \n\t\tDonner la client ID : ");
    scanf("%d",&ID);
    if(!rechercheClient(client,size,ID)){
        printf(" \t\tIl n'y a pas cet ID\n");
        printf(" \t\tClick un nombre pour retourner : ");
        scanf("%d",&i);
        printf("\n");
        Modifier_client();
    }
    clearfile(2);
    for(i=0;i<size;i++){
        if(ID==(client+i)->idClient){
            printf("\t\t1) Donner votre  client ID          :\t");
            scanf("%d",&client[i].idClient);
            printf("\t\t2) Donner votre  client nom         :\t");
            scanf("%s",client[i].nom);
            printf("\t\t3) Donner votre  client prenom      :\t");
            scanf("%s",client[i].prenom);
            printf("\t\t4) Donner votre  client cin         :\t");
            scanf("%d",&client[i].cin);
            printf("\t\t5) Donner votre  client adresse     :\t");
            scanf("%s",client[i].adresse);
            printf("\t\t6) Donner votre  client telephone   :\t");
            scanf("%d",&client[i].telephone);
        }
        clientSendData(client[i]);
    }
    menuGC();
}
void Supprimer_client(){
    int size,i;
    Client *client=clientFetchData(&size);
    Liste_client();
    int ID;
    printf(" \n\t\tDonner la client ID : ");
    scanf("%d",&ID);
    if(!rechercheClient(client,size,ID)){
        printf(" \t\tIl n'y a pas cet ID\n");
        printf(" \t\tClick un nombre pour retourner : ");
        scanf("%d",&i);
        printf("\n");
        Supprimer_client();
    }
    clearfile(2);
    for(i=0;i<size;i++){
        if(ID!=(client+i)->idClient)
            clientSendData(client[i]);
    }
    free(client);
    menuGC();
}

//contrat function
void Ajoute_Contrat(Voiture voiture,Client client){
    int size,i;
    Contrat contrat,*contrats=contratFetchData(&size);
    printf("\n\n\t\t Donner votre numero Contrat        :\t");
    scanf("%f",&contrat.numContrat);
    if(rechercheContrat(contrats,size,contrat.numContrat)){
        free(contrats);
        printf(" \t\tSe ID est  dans  le systeme\n");
        printf(" \t\tClick un nombre pour retourner : ");
        scanf("%d",&i);
        printf("\n");
        Ajoute_Contrat(voiture,client);
    }
    printf("\t\t Donner votre la date de debut : \n");
    printf("\t\t1) Jour  :\t");
    scanf("%d",&contrat.debut.jj);
    printf("\t\t2) Mois  :\t");
    scanf("%d",&contrat.debut.mm);
    printf("\t\t3) Annee :\t");
    scanf("%d",&contrat.debut.an);
    printf("\t\t Donner votre la date de fin : \n");
    printf("\t\t1) Jour  :\t");
    scanf("%d",&contrat.fin.jj);
    printf("\t\t2) Mois  :\t");
    scanf("%d",&contrat.fin.mm);
    printf("\t\t3) Annee :\t");
    scanf("%d",&contrat.fin.an);
    printf("\t\t Donner votre cout :\t");
    contrat.cout=Calculcout(contrat.debut,contrat.fin);
    contrat.idClient=client.idClient;
    contrat.idVoiture=voiture.idVoiture;
    contratSendData(contrat);
}
void Visualiser_contrat(){
    int i,size;
    Contrat *contrat=contratFetchData(&size);
    if(contrat==NULL)
        printf(" \n\t\tPas de contrat pour afficher\n");
    else{
        for(i=0;i<size;i++){
            printf(" \n\t\t1) NumberContract : %f\n  \t\t2) Voiture ID     : %d\n \t\t3) Client ID      : %d\n",contrat[i].numContrat,contrat[i].idVoiture,contrat[i].idClient);
            printf("\t\t Date de Debut : %d/%d/%d\n \t\t Date de Fin   : %d/%d/%d\n \t\t Cout : %d\n",contrat[i].debut.jj,contrat[i].debut.mm,contrat[i].debut.an,contrat[i].fin.jj,contrat[i].fin.mm,contrat[i].fin.an);
        }
    }
    free(contrat);
}
int Louer_voiture(){
    int ID,found=0,reserve=0,i,j,clientSize,voitureSize;
    char nomClient[20],prenomClient[20];
    Client *client=clientFetchData(&clientSize);
    Voiture *voiture=voitureFetchData(&voitureSize);
    if(voiture==NULL || client==NULL){
        printf(" \n\t\tPas de voiture ou client pour afficher\n");
        return 0;
    }
    printf("\t\t Donner le nom de votre client    : ");
    scanf("%s",nomClient);
    printf("\t\t Donner le prenom de votre client : ");
    scanf("%s",prenomClient);
    //checking the client if its exsist
    for(i=0;i<clientSize;i++){
        if(!strcmp(prenomClient,client[i].prenom)&& !strcmp(nomClient,client[i].nom)){
            found=1;
            break;
        }
    }
    //client not exist
    if(found==0){
        printf("\t\t Invalid information, aller a « Gestion clients » pour ingestrire votre  client information!\n");
        menuGC();
    }
    printf("\t\t Donner votre  ID de voiture      : ");
    scanf("%d",&ID);
    found=0;
    // clear the voiture.txt
    clearfile(1);
    //searching for the voiture
    for(j=0;j<voitureSize;j++){
        if(ID==voiture[j].idVoiture){
            found=1;
            //looking if its disponsable
            if(!strcmp(voiture[j].EnLocation,"non")){
                printf("\t\t La voiture n’est pas disponible\n");
                int choice;
                printf("\t\t Entrer un nombre  quelquon pour retourner : ");
                scanf("%s",&choice);
                printf("\n");
                Louer_voiture();
            }
            else{
                // turning it to not disponsable
                strcpy(voiture[j].EnLocation,"non");
                //new contat
                Ajoute_Contrat(voiture[j],client[i]);
                printf("\t\t test\n");
            }
        }
    voitureSendData(voiture[j]);
    }
    //if the car doesnt exist
    if(found==0){
        int choice;
        printf("\t\t La voiture demande n'existe pas\n");
        printf("\t\t Entrer un nombre  quelquon pour retourner : ");
        scanf("%s",&choice);
        printf("\n");
        Louer_voiture();
    }
    free(client);free(voiture);
    menuLV();
}
void Retourner_voiture(){
    int size,i,j,voitureSize;
    float num;
    Contrat *contrat=contratFetchData(&size);
    Voiture *voiture=voitureFetchData(&voitureSize);
    if(voiture==NULL || contrat==NULL){
        if(contrat==NULL)
            printf(" \t\tPas de  contrat\n");
        if(voiture==NULL)
            printf(" \t\tPas de voiture\n");
        free(voiture);
        free(contrat);
        return 0;
    }
    Visualiser_contrat();
    printf(" \n\t\tDonner le numero de contrat tu vas retourner sa voiture : ");
    scanf("%f",&num);
    if(!rechercheContrat(contrat,size,num)){
        free(contrat);
        free(voiture);
        printf(" \t\tSe ID n'est pas dans  le systeme\n");
        printf(" \t\tClick un nombre pour retourner   : ");
        scanf("%d",&i);
        printf("\n");
        Retourner_voiture();
    }
    clearfile(3);
    for(i=0;i<size;i++){
        if(num==contrat[i].numContrat){
            //use MV()
            clearfile(1);
            for(j=0;j<voitureSize;j++){
                if(contrat[i].idVoiture==voiture[j].idVoiture)strcpy(voiture[j].EnLocation,"oui");
                    voitureSendData(voiture[j]);
            }
        }
        else
            contratSendData(contrat[i]);
    }
    menuLV();
}
void Modifier_contrat(){
    int i,contratSize,j,voitureSize,oldvoitureID;
    float num;
    Voiture *voiture=voitureFetchData(&voitureSize);
    Contrat *contrat=contratFetchData(&contratSize);
    if(voiture==NULL || contrat==NULL){
        if(contrat==NULL)
            printf(" \t\tPas de  contrat\n");
        if(voiture==NULL)
            printf(" \t\tPas de voiture\n");
        free(voiture);
        free(contrat);
        return 0;
    }
    Visualiser_contrat();
    printf(" \n\t\tDonner le numero de contrat qui tu as modifier : ");
    scanf("%f",&num);
    if(!rechercheContrat(contrat,contratSize,num)){
        free(contrat);
        free(voiture);
        printf(" \t\tSe ID n'est pas dans  le systeme\n");
        printf(" \t\tClick un nombre pour retourner  : ");
        scanf("%d",&i);
        printf("\n");
        Modifier_contrat();
    }
    clearfile(3);
    clearfile(1);
    for(i=0;i<contratSize;i++){
        if(num==contrat[i].numContrat){
            oldvoitureID=contrat[i].idVoiture;
            printf("\t\t Donner votre neuveau numero Contrat : ");
            scanf("%f",&contrat[i].numContrat);
            printf("\t\t Donner votre neuveau ID voiture     : ");
            scanf("%d",&contrat[i].idVoiture);
            printf("\t\t Donner votre neuveau ID client      : ");
            scanf("%d",&contrat[i].idClient);
            printf("\t\t Donner votre la date de debut : \n");
            printf("\t\t1) Jour  :\t");
            scanf("%d",&contrat[i].debut.jj);
            printf("\t\t2) Mois  :\t");
            scanf("%d",&contrat[i].debut.mm);
            printf("\t\t3) Annee :\t");
            scanf("%d",&contrat[i].debut.an);
            printf("\t\t Donner votre la date de fin : \n");
            printf("\t\t1) Jour  :\t");
            scanf("%d",&contrat[i].fin.jj);
            printf("\t\t2) Mois  :\t");
            scanf("%d",&contrat[i].fin.mm);
            printf("\t\t3) Annee :\t");
            scanf("%d",&contrat[i].fin.an);
            printf("\t\t Donner votre cout :\t");
            contrat[i].cout=Calculcout(contrat[i].debut,contrat[i].fin);
            for(j=0;j<voitureSize;j++){
                if(voiture[j].idVoiture==oldvoitureID){
                    strcpy(voiture[j].EnLocation,"oui");
                }
                if(voiture[j].idVoiture==contrat[i].idVoiture){
                    strcpy(voiture[j].EnLocation,"non");
                }
                voitureSendData(voiture[j]);
            }
        }
        contratSendData(contrat[i]);
    }
    free(voiture);
    free(contrat);
    menuLV();
}
int Supprimer_contrat(){
    int i,j,contratSize,voitureSize;
    Contrat *contrat=contratFetchData(&contratSize);
    Voiture *voiture=voitureFetchData(&voitureSize);
    if(voiture==NULL || contrat==NULL){
        if(contrat==NULL)
            printf(" \t\tPas de  contrat\n");
        if(voiture==NULL)
            printf(" \t\tPas de voiture\n");
        free(voiture);
        free(contrat);
        return 0;
    }
    Visualiser_contrat();
    float num;
    //fscanf u should put all the variables all the line get it
    printf(" \n\t\tDonner le num contrat          : ");
    scanf("%f",&num);
    if(!rechercheContrat(contrat,contratSize,num)){
        free(contrat);
        free(voiture);
        printf(" \t\tSe ID n'est pas dans  le systeme\n");
        printf(" \t\tClick un nombre pour retourner : ");
        scanf("%d",&i);
        printf("\n");
        Supprimer_contrat();
    }
    clearfile(3);
    clearfile(1);
    for(i=0;i<contratSize;i++){
        if(num!=contrat[i].numContrat)
            contratSendData(contrat[i]);
        else{
            for(j=0;j<voitureSize;j++){
                if(contrat[i].idVoiture==voiture[j].idVoiture)strcpy(voiture[j].EnLocation,"oui");
                    voitureSendData(voiture[j]);
            }
        }
    }
    free(voiture);
    free(contrat);
    menuLV();
};

//menu
void menuLV(){
    system("cls");
    int c=0;
    printf("\n");
    printf("\n\t\t\t\t\t~~~~~~~~~~~~Location d'une Voiture~~~~~~~~~~~~\n");
    printf("\t\t\t\t\t-----------------------------------------------\n");
    printf("\t\t\t\t\t#Visualiser contrat...........................1\n");
    printf("\t\t\t\t\t#Louer voiture................................2\n");
    printf("\t\t\t\t\t#Retourner Voiture............................3\n");
    printf("\t\t\t\t\t#Modifier contrat.............................4\n");
    printf("\t\t\t\t\t#Supprimer contrat............................5\n");
    printf("\t\t\t\t\t#Retour.......................................6\n");
    printf("\t\t\t\t\t-----------------------------------------------\n");
    printf("\n\t\t\t\t\t\t Vorte  choix : ");
    scanf("%d",&c);
    switch(c){
    case 1:
        Visualiser_contrat();
        break;
    case 2:
        Louer_voiture();
        break;
    case 3:
        Retourner_voiture();
        break;
    case 4:
        Modifier_contrat();
        break;
    case 5:
        Supprimer_contrat();
        break;
    case 6:
        main();
        break;
    default:
        erreur();
    }
}
void menuGV(){
    system("cls");
    int c=0;
    printf("\n");
    printf("\n\t\t\t\t\t~~~~~~~~~~~Gestion des voitures~~~~~~~~~~~\n");
    printf("\t\t\t\t\t------------------------------------------\n");
    printf("\t\t\t\t\t#Liste des voitures......................1\n");
    printf("\t\t\t\t\t#Ajoute  voiture.........................2\n");
    printf("\t\t\t\t\t#Modifier Voiture........................3\n");
    printf("\t\t\t\t\t#Supprimer Voiture.......................4\n");
    printf("\t\t\t\t\t#Retour..................................5\n");
    printf("\t\t\t\t\t------------------------------------------\n");
    printf("\n\t\t\t\t\t\t Vorte  choix : ");
    scanf("%d",&c);
    switch(c){
    case 1:
        Liste_voiture();
        break;
    case 2:
        Ajouter_voiture();
        break;
    case 3:
        Modifier_voiture();
        break;
    case 4:
        Supprimer_voiture() ;
        break;
    case 5:
        main();
        break;
    default:
        erreur();
    }
}
void menuGC(){
    system("cls");
    int c=0;
    printf("\n");
    printf("\n\t\t\t\t\t~~~~~~~~~~~Gestion des clients~~~~~~~~~~~\n");
    printf("\t\t\t\t\t-----------------------------------------\n");
    printf("\t\t\t\t\t#Liste des Clients......................1\n");
    printf("\t\t\t\t\t#Ajouter client.........................2\n");
    printf("\t\t\t\t\t#Modifier client........................3\n");
    printf("\t\t\t\t\t#Supprimer client.......................4\n");
    printf("\t\t\t\t\t#Retour.................................5\n");
    printf("\t\t\t\t\t-----------------------------------------\n");
    printf("\n\t\t\t\t\t\t Votre  choix : ");
    scanf("%d",&c);
    switch(c){
    case 1:
        Liste_client();
        break;
    case 2:
        Ajoute_client();
        break;
    case 3:
        Modifier_client();
        break;
    case 4:
        Supprimer_client();
        break;
    case 5:
        main();
        break;
    default:
        erreur();
    }
}
void (*GestionLocation[4])(void)={menuLV,menuGV,menuGC,quitter};
void (*menuP(void))(void){
    int choix;
    do{
        printf("\n");
        printf("\n\t\t\t\t\t~~~~~~~~~~~Menu Principale~~~~~~~~~~~\n");
        printf("\t\t\t\t\t-------------------------------------\n");
        printf("\t\t\t\t\t#Location...........................1\n");
        printf("\t\t\t\t\t#Gestion voitures...................2\n");
        printf("\t\t\t\t\t#Gestion clients....................3\n");
        printf("\t\t\t\t\t#Quitter............................4\n");
        printf("\t\t\t\t\t-------------------------------------\n");
        printf("\n\t\t\t\t\t\tVotre choix:");
        scanf("%d",&choix);
    }while(choix<0 || choix>4);
    if(choix==4) return NULL;
return GestionLocation[choix-1];
}

int main(){
    system("cls");
    void (*fp)(void)=menuP();
    if(fp)fp();
return 0;
}
