//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "Waz_form.h"
#include "Opc.h"
#include "About_f.h"
#include <fstream.h>
#include <mmsystem.h>
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define bmKANVAS 0
#define bmMAPA   1
#define bmNIC    2
#define bmKROPA  3
#define bmGLOWA  4
#define bmZBIER  5
#define bmBONUS  6
#define bmCLOCK  7

Graphics::TBitmap* bitmap[8];

bool sndEx = FileExists("pauza.wav") && FileExists("zbier.wav") && FileExists("clock.wav") && FileExists("bonus.wav") && FileExists("stop.wav");
AnsiString plikName;
long plikIndex = 0;

long im = 0;
char ruch[2][1024*64];
long punktow = 0;

long czas = 0, czasOld = 0;

#define ZBIER 0
#define BONUS 1
#define CLOCK 2

struct __gra
{
 char mapka[80][80];
 long wazCnt;
 char extra[3][2][80];
 long extraCnt[3];
POINT pos, mov, cnt;
float reftime, igntime, ref_mul, ign_mul;

} level, gra;

 //---------------------------------------------------------------------------
TMainForm *MainForm;
 //---------------------------------------------------------------------------
__fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner),gram(false),stop(false),pauza(false)
{
    hInst = (HINSTANCE)HInstance;
for (int i = 0; i < 8; i++)
     bitmap[i] = new Graphics::TBitmap;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormKeyDown(TObject *Sender, WORD &key,TShiftState Shift)
{
switch (key)
  {
    case 27:
         if (Stop->Enabled==false)
             return;
         StopClick(this);
    break;
    case 71:
         if (plikIndex==0 || Start->Enabled==false)
             return;
         GrajFunk();
    break;
    case 80:
         if (Pauza->Enabled==false)
             return;
         PauzaClick(this);
    break;
    case 79:
         if (Opcje->Enabled==false)
             return;
         OpcjeClick(this);
    break;
    case 65:
         if (About->Enabled==false)
             return;
         AboutClick(this);
    break;
   }
if (gram==false || stop==true)
    return;

switch (key)
   {
    case VK_LEFT:
         if (gra.mov.y!=0)
            {if (ruch[0][im] > 0)
             if (gra.mapka[(int)ruch[0][im]-1][(int)ruch[1][im]]=='1')
                 return;
            }
         if (gra.mov.x>0)
             return;
         if (gra.mov.x<0)
            {czasOld -= gra.reftime/2;
             return;
            }
         gra.mov.x = -1;
         gra.mov.y = 0;
    break;
    case VK_RIGHT:
         if (gra.mov.y!=0)
            {if (ruch[0][im] < gra.cnt.x-1)
             if (gra.mapka[(int)ruch[0][im]+1][(int)ruch[1][im]]=='1')
                 return;
            }
         if (gra.mov.x<0)
             return;
         if (gra.mov.x>0)
            {czasOld -= gra.reftime/2;
             return;
            }
         gra.mov.x = +1;
         gra.mov.y = 0;
    break;
    case VK_DOWN:
         if (gra.mov.x!=0)
            {if (ruch[1][im] < gra.cnt.y-1)
             if (gra.mapka[(int)ruch[0][im]][(int)ruch[1][im]+1]=='1')
                 return;
            }
         if (gra.mov.y<0)
             return;
         if (gra.mov.y>0)
            {czasOld -= gra.reftime/2;
             return;
            }
         gra.mov.x = 0;
         gra.mov.y = +1;
    break;
    case VK_UP:
         if (gra.mov.x!=0)
            {if (ruch[1][im] > 0)
             if (gra.mapka[(int)ruch[0][im]][(int)ruch[1][im]-1]=='1')
                 return;
            }
         if (gra.mov.y>0)
             return;
         if (gra.mov.y<0)
            {czasOld -= gra.reftime/2;
             return;
            }
         gra.mov.x = 0;
         gra.mov.y = -1;
    break;
   }
gram = false;
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::FormCreate(TObject *Sender)
{
 gram = false;
pauza = false;
 stop = true;

bitmap[bmKANVAS]->Height = 1024;
 bitmap[bmKANVAS]->Width = 1024;
bitmap[bmKANVAS]->LoadFromResourceName((int)hInst,"LOGO");

 bitmap[bmKROPA]->LoadFromFile("kropa.bmp");
 bitmap[bmGLOWA]->LoadFromFile("glowa.bmp");
   bitmap[bmNIC]->LoadFromFile("nic.bmp");
 bitmap[bmZBIER]->LoadFromFile("zbier.bmp");
 bitmap[bmBONUS]->LoadFromFile("bonus.bmp");
 bitmap[bmCLOCK]->LoadFromFile("clock.bmp");
  bitmap[bmMAPA]->LoadFromFile("mapa.bmp");

setmem(&level,sizeof(level),0x00);

int searchRet;
struct TSearchRec pliki;
for (searchRet = FindFirst("*.lev",faAnyFile,pliki), plikIndex = 0; !searchRet && plikIndex < 12; searchRet = FindNext(pliki))
    {
     switch (++plikIndex)
    {
    case 1:
          N11->Visible = true;
          N11->Enabled = true;
          N11->Caption = pliki.Name;
    break;
    case 2:
          N21->Visible = true;
          N21->Enabled = true;
          N21->Caption = pliki.Name;
    break;
    case 3:
          N31->Visible = true;
          N31->Enabled = true;
          N31->Caption = pliki.Name;
    break;
    case 4:
          N41->Visible = true;
          N41->Enabled = true;
          N41->Caption = pliki.Name;
    break;
    case 5:
          N51->Visible = true;
          N51->Enabled = true;
          N51->Caption = pliki.Name;
    break;
    case 6:
          N61->Visible = true;
          N61->Enabled = true;
          N61->Caption = pliki.Name;
    break;
    case 7:
          N71->Visible = true;
          N71->Enabled = true;
          N71->Caption = pliki.Name;
    break;
    case 8:
          N81->Visible = true;
          N81->Enabled = true;
          N81->Caption = pliki.Name;
    break;
    case 9:
          N91->Visible = true;
          N91->Enabled = true;
          N91->Caption = pliki.Name;
    break;
    case 10:
         N101->Visible = true;
         N101->Enabled = true;
         N101->Caption = pliki.Name;
    break;
    case 11:
         N111->Visible = true;
         N111->Enabled = true;
         N111->Caption = pliki.Name;
    break;
    case 12:
         N121->Visible = true;
         N121->Enabled = true;
         N121->Caption = pliki.Name;
    break;
   }
    }
MainForm->Repaint();
MainForm->Show();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Load(void)
{
bitmap[bmKANVAS]->Height = 1024;
 bitmap[bmKANVAS]->Width = 1024;

setmem(&gra,sizeof(gra),0x00);

 TRect tempRect = Rect(0,0,bitmap[bmKANVAS]->Width, bitmap[bmKANVAS]->Height);
bitmap[bmKANVAS]->Canvas->Brush->Color = clBlack;
bitmap[bmKANVAS]->Canvas->FillRect(tempRect);
MainForm->Caption = "Level : " + plikName;
if (!FileExists(plikName.c_str()))
   {ShowMessage("Nie ma pliku konfiguracji");
    return;
   }
char lineBuf[256] = "";
ifstream plikHnd;
plikHnd.open(plikName.c_str());
for (level.cnt.y = 0; !plikHnd.eof(); level.cnt.y++) // konfig parametry
    {
     if (!plikHnd.getline(lineBuf,sizeof(lineBuf)))
         break;
     if (strstr(lineBuf,"end!")!=NULL)
        {break;
        }
     if (strstr(lineBuf,"pos.x")!=NULL)
        {strtok(lineBuf,"=");
            level.pos.x = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"pos.y")!=NULL)
        {strtok(lineBuf,"=");
            level.pos.y = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"mov.x")!=NULL)
        {strtok(lineBuf,"=");
            level.mov.x = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"mov.y")!=NULL)
        {strtok(lineBuf,"=");
            level.mov.y = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"dlugosc")!=NULL)
        {strtok(lineBuf,"=");
      level.wazCnt = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"zbierek")!=NULL)
        {strtok(lineBuf,"=");
      level.extraCnt[ZBIER] = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"bonusow")!=NULL)
        {strtok(lineBuf,"=");
      level.extraCnt[BONUS] = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"clockow")!=NULL)
        {strtok(lineBuf,"=");
      level.extraCnt[CLOCK] = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"reftime")!=NULL)
        {strtok(lineBuf,"=");
         level.reftime = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"ref_mul")!=NULL)
        {strtok(lineBuf,"=");
         level.ref_mul = strtod(strtok(NULL,""),NULL);
         continue;
        }
     if (strstr(lineBuf,"igntime")!=NULL)
        {strtok(lineBuf,"=");
         level.igntime = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(lineBuf,"ign_mul")!=NULL)
        {strtok(lineBuf,"=");
         level.ign_mul = strtod(strtok(NULL,""),NULL);
         continue;
        }
    }
 if (plikHnd.eof())
    {ShowMessage("Plik konfiguracji jest nieprawid³owy!");
     return;
    }
for (level.cnt.y = 0, level.cnt.x = 0; !plikHnd.eof(); level.cnt.y++)
    {
      if (!plikHnd.getline(lineBuf,sizeof(lineBuf)))
          break;
     for (int t = 0, tmax = strlen(lineBuf); t < tmax; t++)
         {
          if ((int)lineBuf[t]=='0')
          bitmap[bmKANVAS]->Canvas->Draw(t*bitmap[bmNIC]->Height,level.cnt.y*bitmap[bmNIC]->Height,bitmap[bmNIC]);
          else
          if ((int)lineBuf[t]=='1')
          bitmap[bmKANVAS]->Canvas->Draw(t*bitmap[bmNIC]->Height,level.cnt.y*bitmap[bmNIC]->Height,bitmap[bmMAPA]);

          level.mapka[t][level.cnt.y] = lineBuf[t];
         }
      if (level.cnt.x < strlen(lineBuf))
          level.cnt.x = strlen(lineBuf);
    }
plikHnd.close();

  bitmap[bmKANVAS]->Width = bitmap[bmNIC]->Height * level.cnt.x;
MainForm->Left =  (Screen->Width - bitmap[bmKANVAS]->Width)/2;
MainForm->ClientWidth = bitmap[bmKANVAS]->Width;
 bitmap[bmKANVAS]->Height = bitmap[bmNIC]->Height * level.cnt.y;
 MainForm->Top = (Screen->Height - bitmap[bmKANVAS]->Height)/2;
MainForm->ClientHeight = bitmap[bmKANVAS]->Height;

pauza = false;
 stop = true;
 gram = false;

Start->Enabled = true;
 Stop->Enabled = false;
Pauza->Enabled = false;

setmem(&gra,sizeof(gra),0x00);

MainForm->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::GrajFunk(void)
{
if (gram==true)
    return;

pauza = false;
 stop = false;
 gram = true;

Start->Enabled = false;
 Stop->Enabled = true;
Pauza->Enabled = true;

memmove(&gra,&level,sizeof(level));

im = 0;
ruch[0][im] = gra.pos.x;
ruch[1][im] = gra.pos.y;

randomize();
for (int nr = 0; nr < gra.extraCnt[ZBIER]; nr++)
    {
     do {
         gra.extra[ZBIER][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[ZBIER][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[ZBIER][0][nr]][gra.extra[ZBIER][1][nr]]!='0');

     gra.mapka[gra.extra[ZBIER][0][nr]][gra.extra[ZBIER][1][nr]]='2';
    }
for (int nr = 0; nr < gra.extraCnt[BONUS]; nr++)
    {
     do {
         gra.extra[BONUS][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[BONUS][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[BONUS][0][nr]][gra.extra[BONUS][1][nr]]!='0');

     gra.mapka[gra.extra[BONUS][0][nr]][gra.extra[BONUS][1][nr]]='3';
    }
for (int nr = 0; nr < gra.extraCnt[CLOCK]; nr++)
    {
     do {
         gra.extra[CLOCK][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[CLOCK][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[CLOCK][0][nr]][gra.extra[CLOCK][1][nr]]!='0');

     gra.mapka[gra.extra[CLOCK][0][nr]][gra.extra[CLOCK][1][nr]]='4';
    }
Repaint();

punktow = 0;
MainForm->Caption = "Grasz : 0 punktów w level \""+plikName+"\"";
Ruch();
StopClick(this);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Ruch(void)
{
do {

    do { Sleep(10);
         czas = timeGetTime();
         Application->ProcessMessages();
       } while (pauza==true);
    if (czas-czasOld < gra.reftime)
        continue;
    gram = true;

    im = (im+1) % (sizeof(ruch)/2);

    gra.pos.x = gra.pos.x + gra.mov.x;
    if (gra.pos.x>= gra.cnt.x)
        gra.pos.x = 0;
    else
    if (gra.pos.x < 0)
        gra.pos.x = gra.cnt.x-1;
    ruch[0][im] = gra.pos.x;

    gra.pos.y = gra.pos.y + gra.mov.y;
    if (gra.pos.y>= gra.cnt.y)
        gra.pos.y = 0;
    else
    if (gra.pos.y < 0)
        gra.pos.y = gra.cnt.y-1;
    ruch[1][im] = gra.pos.y;

    Zbieraj();

    if (im>=gra.wazCnt)
       {gra.mapka[ruch[0][im-gra.wazCnt]][ruch[1][im-gra.wazCnt]]='0';
       }
    if (gra.mapka[ruch[0][im]][ruch[1][im]]=='1')
       {gram = false;
        stop = true;
        --im;
        return;
       }
    else gra.mapka[ruch[0][im]][ruch[1][im]]='1';

    if (im>0 && gra.wazCnt>1)
       {MainForm->Canvas->Draw(ruch[0][im-1]*bitmap[bmNIC]->Height,ruch[1][im-1]*bitmap[bmNIC]->Height,bitmap[bmKROPA]);
       }
    if (im>=gra.wazCnt)
       {MainForm->Canvas->Draw(ruch[0][im-gra.wazCnt]*bitmap[bmNIC]->Height,ruch[1][im-gra.wazCnt]*bitmap[bmNIC]->Height,bitmap[bmNIC]);
       }

    MainForm->Canvas->Draw(ruch[0][im]*bitmap[bmNIC]->Height,ruch[1][im]*bitmap[bmNIC]->Height,bitmap[bmGLOWA]);

    if (gra.reftime > gra.ref_mul)
    gra.reftime = gra.reftime*(1 - gra.ref_mul);
    if (gra.igntime > gra.ign_mul)
    gra.igntime = gra.igntime*(1 - gra.ign_mul);

    czasOld = timeGetTime();

    if (gra.mov.x>0 ? gra.mapka[(int)ruch[0][im]+1][(int)ruch[1][im]+0]=='1' : false)
        czasOld+=gra.igntime;
    else
    if (gra.mov.x<0 ? gra.mapka[(int)ruch[0][im]-1][(int)ruch[1][im]+0]=='1' : false)
        czasOld+=gra.igntime;
    else
    if (gra.mov.y>0 ? gra.mapka[(int)ruch[0][im]+0][(int)ruch[1][im]+1]=='1' : false)
        czasOld+=gra.igntime;
    else
    if (gra.mov.y<0 ? gra.mapka[(int)ruch[0][im]+0][(int)ruch[1][im]-1]=='1' : false)
        czasOld+=gra.igntime;

   } while (stop==false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Zbieraj(void)
{
if (gram==false)
    return;

randomize();
for (int nr = 0; nr < gra.extraCnt[ZBIER]; nr++)
    {
     if ((int)ruch[0][im]!=(int)gra.extra[ZBIER][0][nr] || (int)ruch[1][im]!=(int)gra.extra[ZBIER][1][nr])
         continue;

     if (gra.reftime < level.reftime)
     gra.reftime = gra.reftime*(1 + gra.cnt.x*gra.ref_mul);
     if (gra.igntime < level.igntime)
     gra.igntime = gra.igntime*(1 + gra.cnt.x*gra.ign_mul);

     gra.wazCnt++;
     punktow += int(100*level.reftime/gra.reftime);
     if (sndEx)
         sndPlaySound("zbier.wav", SND_ASYNC | SND_FILENAME);

     MainForm->Canvas->Draw(gra.extra[ZBIER][0][nr]*bitmap[bmNIC]->Height,gra.extra[ZBIER][1][nr]*bitmap[bmNIC]->Height,bitmap[bmNIC]);
     do {
         gra.extra[ZBIER][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[ZBIER][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[ZBIER][0][nr]][gra.extra[ZBIER][1][nr]]!='0');

      gra.mapka[gra.extra[ZBIER][0][nr]][gra.extra[ZBIER][1][nr]] = '2';
     MainForm->Canvas->Draw(gra.extra[ZBIER][0][nr]*bitmap[bmNIC]->Height,gra.extra[ZBIER][1][nr]*bitmap[bmNIC]->Height,bitmap[bmZBIER]);
    }
for (int nr = 0; nr < gra.extraCnt[CLOCK]; nr++)
    {
     if (im%gra.cnt.x==0) goto clockLOS;
     else
     if ((int)ruch[0][im]!=(int)gra.extra[CLOCK][0][nr] || (int)ruch[1][im]!=(int)gra.extra[CLOCK][1][nr])
         continue;

     if (gra.reftime < level.reftime)
     gra.reftime = gra.reftime*(1 + gra.cnt.x*gra.ref_mul*5);
     if (gra.igntime < level.igntime)
     gra.igntime = gra.igntime*(1 + gra.cnt.x*gra.ign_mul*5);

     gra.wazCnt+=5;

     punktow -= int(5*100);
     if (sndEx)
         sndPlaySound("clock.wav", SND_ASYNC | SND_FILENAME);

clockLOS:
     MainForm->Canvas->Draw(gra.extra[CLOCK][0][nr]*bitmap[bmNIC]->Height,gra.extra[CLOCK][1][nr]*bitmap[bmNIC]->Height,bitmap[bmNIC]);
     do {
         gra.extra[CLOCK][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[CLOCK][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[CLOCK][0][nr]][gra.extra[CLOCK][1][nr]]!='0');

        gra.mapka[gra.extra[CLOCK][0][nr]][gra.extra[CLOCK][1][nr]] = '4';
     MainForm->Canvas->Draw(gra.extra[CLOCK][0][nr]*bitmap[bmNIC]->Height,gra.extra[CLOCK][1][nr]*bitmap[bmNIC]->Height,bitmap[bmCLOCK]);
    }
for (int nr = 0; nr < gra.extraCnt[BONUS]; nr++)
    {
     if (im%(gra.cnt.x+gra.cnt.y)==0) goto bonusLOS;
     else
     if ((int)ruch[0][im]!=(int)gra.extra[BONUS][0][nr] || (int)ruch[1][im]!=(int)gra.extra[BONUS][1][nr])
         continue;

     for (int zzz = 0; zzz <= 5; zzz++)
         {
          if (gra.wazCnt <= zzz)
              break;
          gra.mapka[ruch[0][im-gra.wazCnt+zzz]][ruch[1][im-gra.wazCnt+zzz]] = '0';
          MainForm->Canvas->Draw(ruch[0][im-gra.wazCnt+zzz]*bitmap[bmNIC]->Height,ruch[1][im-gra.wazCnt+zzz]*bitmap[bmNIC]->Height,bitmap[bmNIC]);
         }
     if  (gra.wazCnt<=5) gra.wazCnt = 1;
     else gra.wazCnt-=5;

     if (gra.reftime < level.reftime)
     gra.reftime = gra.reftime*(1 - gra.cnt.x*gra.ref_mul*5);
     if (gra.igntime < level.igntime)
     gra.igntime = gra.igntime*(1 - gra.cnt.x*gra.ign_mul*5);

     punktow -= int(5*100);
     if (sndEx)
         sndPlaySound("bonus.wav", SND_ASYNC | SND_FILENAME);
 bonusLOS:
     MainForm->Canvas->Draw(gra.extra[BONUS][0][nr]*bitmap[bmNIC]->Height,gra.extra[BONUS][1][nr]*bitmap[bmNIC]->Height,bitmap[bmNIC]);
     do {
         gra.extra[BONUS][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[BONUS][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[BONUS][0][nr]][gra.extra[BONUS][1][nr]]!='0');

        gra.mapka[gra.extra[BONUS][0][nr]][gra.extra[BONUS][1][nr]] = '3';
     MainForm->Canvas->Draw(gra.extra[BONUS][0][nr]*bitmap[bmNIC]->Height,gra.extra[BONUS][1][nr]*bitmap[bmNIC]->Height,bitmap[bmBONUS]);
    }
MainForm->Caption = "Grasz : "+(String)punktow+" punktów w levelu \""+plikName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormPaint(TObject *Sender)
{
Canvas->CopyRect(Canvas->ClipRect,bitmap[bmKANVAS]->Canvas,Canvas->ClipRect);

//if (gra==false)
//    return;
for (int nr = 0; nr < gra.extraCnt[CLOCK]; nr++)
    {MainForm->Canvas->Draw(gra.extra[CLOCK][0][nr]*bitmap[bmNIC]->Height,gra.extra[CLOCK][1][nr]*bitmap[bmNIC]->Height,bitmap[bmCLOCK]);
    }
for (int nr = 0; nr < gra.extraCnt[BONUS]; nr++)
    {MainForm->Canvas->Draw(gra.extra[BONUS][0][nr]*bitmap[bmNIC]->Height,gra.extra[BONUS][1][nr]*bitmap[bmNIC]->Height,bitmap[bmBONUS]);
    }
for (int nr = 0; nr < gra.extraCnt[ZBIER]; nr++)
    {MainForm->Canvas->Draw(gra.extra[ZBIER][0][nr]*bitmap[bmNIC]->Height,gra.extra[ZBIER][1][nr]*bitmap[bmNIC]->Height,bitmap[bmZBIER]);
    }
for (int nr = 1; nr < gra.wazCnt; nr++)
    {if (im>=nr)
         MainForm->Canvas->Draw(ruch[0][im-nr]*bitmap[bmNIC]->Height,ruch[1][im-nr]*bitmap[bmNIC]->Height,bitmap[bmKROPA]);
    }
 if (gra.wazCnt > 0)
     MainForm->Canvas->Draw(ruch[0][im]*bitmap[bmNIC]->Height,ruch[1][im]*bitmap[bmNIC]->Height,bitmap[bmGLOWA]);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpcjeClick(TObject *Sender)
{
OpcjeForm->UpDown1->Position = level.wazCnt;
OpcjeForm->UpDown2->Position = level.reftime;
OpcjeForm->UpDown3->Position = level.extraCnt[ZBIER];

OpcjeForm->ShowModal();

level.extraCnt[ZBIER] = OpcjeForm->UpDown3->Position;
   level.reftime = OpcjeForm->UpDown2->Position;
level.wazCnt = OpcjeForm->UpDown1->Position;

OpcjeForm->Edit3->Text = level.extraCnt[ZBIER];
OpcjeForm->Edit2->Text = level.reftime;
OpcjeForm->Edit1->Text = level.wazCnt;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PauzaClick(TObject *Sender)
{
if (stop==true)
    return;
pauza=!pauza;
if (sndEx)
    sndPlaySound("pauza.wav", SND_ASYNC | SND_FILENAME);
if (pauza==true) MainForm->Caption = "Pauza : " + (String)punktow + " punktów w levelu \""+plikName+"\"";
else MainForm->Caption = "Grasz : " + (String)punktow + " punktów w levelu \""+plikName+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StopClick(TObject *Sender)
{
Start->Enabled = true;
 Stop->Enabled = false;
Pauza->Enabled = false;
 pauza = false;
  gram = false;
  stop = true;
if (sndEx)
    sndPlaySound("stop.wav", SND_ASYNC | SND_FILENAME);
MainForm->Caption = "Koniec : "+(String)punktow+" punktów w levelu "+plikName;
}
//---------------------------------------------------------------------------


void __fastcall TMainForm::FormDestroy(TObject *Sender)
{
pauza = false;
 stop = true;
for (int i = 0; i < 8; i++)
     delete bitmap[i];
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormClose(TObject *Sender, TCloseAction &Action)
{
pauza = false;
 stop = true;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::AboutClick(TObject *Sender)
{
AboutBox->ShowModal();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::ZamknijClick(TObject *Sender)
{
StopClick(Sender);
Close();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N11Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N11->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N21Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N21->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N31Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N31->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N41Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N41->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N51Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N51->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N61Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N61->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N71Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N71->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N81Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N81->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N91Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N91->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N101Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N101->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N111Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N111->Caption;
Load();
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N121Click(TObject *Sender)
{
if (gram==true)
    return;
plikName = N121->Caption;
Load();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StartClick(TObject *Sender)
{
if (plikIndex!=0)
    GrajFunk();
}
//---------------------------------------------------------------------------

