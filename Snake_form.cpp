//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
#include "Snake_form.h"
#include "Opc.h"
#include "../../FORM_TEMPLATES/About_frm.h"
#include "Unit1.h"
//---------------------------------------------------------------------------
#include <mmsystem.h>
#include <fstream.h>
#pragma package(smart_init)
#pragma resource "*.dfm"
//---------------------------------------------------------------------------
enum {
BM_ZBIER  = 0,
BM_BONUS  = 1,
BM_CLOCK  = 2,
BM_CANVAS = 3,
BM_MAPA   = 4,
BM_NIC    = 5,
BM_KROPA  = 6,
BM_GLOWA  = 7
};
//---------------------------------------------------------------------------
enum {
ZB_ZBIER = 0,
ZB_BONUS = 1,
ZB_CLOCK = 2
};
//---------------------------------------------------------------------------
TMainForm *MainForm;
 //---------------------------------------------------------------------------
struct __plik plik[13];
struct TSearchRec plik_search;
int plik_search_ret;

struct { AnsiString Name;
long Index;
} plik_current;

Graphics::TBitmap* bitmap[8];
bool sound_exists = FileExists("pauza.wav") && FileExists("zbier.wav") && FileExists("clock.wav") && FileExists("bonus.wav") && FileExists("stop.wav");

long mapa = 0;
long im = 0;
char ruch[2][1024*64];
long punktow = 0;
long czas = 0, czas_old = 0;

struct {
 char mapka[80][80];
 long waz_cnt;
 char extra[3][2][80];
 long extra_cnt[3];
POINT pos, mov, cnt;
float reftime, igntime, ref_mul, ign_mul;
} level, gra;
//---------------------------------------------------------------------------

void __fastcall TMainForm::Levele()
{
for (plik_search_ret = FindFirst("*.lev",faAnyFile,plik_search), plik_current.Index = 0; !plik_search_ret && plik_current.Index < 12; plik_search_ret = FindNext(plik_search))
    {
     ++plik_current.Index;
     plik[plik_current.Index].Name = plik_search.Name;

     switch (plik_current.Index)
    	{
	    case 1:
	          N11->Visible = true;
	          N11->Enabled = true;
	          N11->Caption = plik_search.Name;
	    break;
	    case 2:
	          N21->Visible = true;
	          N21->Enabled = true;
	          N21->Caption = plik_search.Name;
	    break;
	    case 3:
	          N31->Visible = true;
	          N31->Enabled = true;
	          N31->Caption = plik_search.Name;
	    break;
	    case 4:
	          N41->Visible = true;
	          N41->Enabled = true;
	          N41->Caption = plik_search.Name;
	    break;
	    case 5:
	          N51->Visible = true;
	          N51->Enabled = true;
	          N51->Caption = plik_search.Name;
	    break;
	    case 6:
	          N61->Visible = true;
	          N61->Enabled = true;
	          N61->Caption = plik_search.Name;
	    break;
	    case 7:
	          N71->Visible = true;
	          N71->Enabled = true;
	          N71->Caption = plik_search.Name;
	    break;
	    case 8:
	          N81->Visible = true;
	          N81->Enabled = true;
	          N81->Caption = plik_search.Name;
	    break;
	    case 9:
	          N91->Visible = true;
	          N91->Enabled = true;
	          N91->Caption = plik_search.Name;
	    break;
	    case 10:
	         N101->Visible = true;
	         N101->Enabled = true;
	         N101->Caption = plik_search.Name;
	    break;
	    case 11:
	        N111->Visible = true;
	         N111->Enabled = true;
	         N111->Caption = plik_search.Name;
	    break;
	    case 12:
	         N121->Visible = true;
	         N121->Enabled = true;
	         N121->Caption = plik_search.Name;
	    break;
	   }
	}
}
//---------------------------------------------------------------------------

 __fastcall TMainForm::TMainForm(TComponent* Owner)
    : TForm(Owner),gram(false),stop(false),pauza(false),hInst((HINSTANCE)HInstance)
{
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
         if (plik_current.Index==0 || Start->Enabled==false)
             return;
         Graj();
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
            {czas_old -= gra.reftime/2;
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
            {czas_old -= gra.reftime/2;
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
            {czas_old -= gra.reftime/2;
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
            {czas_old -= gra.reftime/2;
             return;
            }
         gra.mov.x = 0;
         gra.mov.y = -1;
    break;
   }
gram = false;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Sound(AnsiString a_plik_name)
{
sndPlaySoundA(a_plik_name.c_str(), SND_ASYNC | SND_FILENAME);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Load(AnsiString a_plik_name)
{
bitmap[BM_CANVAS]->Height = 2048;
bitmap[BM_CANVAS]->Width = 1024;

setmem(&gra,sizeof(gra),0x00);

 TRect tempRect = Rect(0,0,bitmap[BM_CANVAS]->Width, bitmap[BM_CANVAS]->Height);
bitmap[BM_CANVAS]->Canvas->Brush->Color = clBlack;
bitmap[BM_CANVAS]->Canvas->FillRect(tempRect);
MainForm->Caption = "Level : " + a_plik_name;
if (!FileExists(GetCurrentDir() + "\\" + a_plik_name))
   {ShowMessage("Nie ma pliku konfiguracji: " + a_plik_name);
    return;
   }
char line_buf[512] = "";
ifstream plik_hnd;
plik_hnd.open(a_plik_name.c_str());
for (level.cnt.y = 0; !plik_hnd.eof(); level.cnt.y++) // konfig parametry
    {
     if (!plik_hnd.getline(line_buf,sizeof(line_buf)))
         break;
     if (strstr(line_buf,"end!")!=NULL)
        {break;
        }
     if (strstr(line_buf,"pos.x")!=NULL)
        {strtok(line_buf,"=");
            level.pos.x = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"pos.y")!=NULL)
        {strtok(line_buf,"=");
            level.pos.y = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"mov.x")!=NULL)
        {strtok(line_buf,"=");
            level.mov.x = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"mov.y")!=NULL)
        {strtok(line_buf,"=");
            level.mov.y = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"dlugosc")!=NULL)
        {strtok(line_buf,"=");
      level.waz_cnt = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"zbierek")!=NULL)
        {strtok(line_buf,"=");
      level.extra_cnt[ZB_ZBIER] = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"bonusow")!=NULL)
        {strtok(line_buf,"=");
      level.extra_cnt[ZB_BONUS] = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"clockow")!=NULL)
        {strtok(line_buf,"=");
      level.extra_cnt[ZB_CLOCK] = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"reftime")!=NULL)
        {strtok(line_buf,"=");
         level.reftime = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"ref_mul")!=NULL)
        {strtok(line_buf,"=");
         level.ref_mul = strtod(strtok(NULL,""),NULL);
         continue;
        }
     if (strstr(line_buf,"igntime")!=NULL)
        {strtok(line_buf,"=");
         level.igntime = strtol(strtok(NULL,""),NULL,10);
         continue;
        }
     if (strstr(line_buf,"ign_mul")!=NULL)
        {strtok(line_buf,"=");
         level.ign_mul = strtod(strtok(NULL,""),NULL);
         continue;
        }
    }
 if (plik_hnd.eof())
    {ShowMessage("Plik konfiguracji jest nieprawid�owy!");
     return;
    }
for (level.cnt.y = 0, level.cnt.x = 0; !plik_hnd.eof(); level.cnt.y++)
    {
      if (!plik_hnd.getline(line_buf,sizeof(line_buf)))
          break;
     for (int t = 0, tmax = strlen(line_buf); t < tmax; t++)
         {
          if ((int)line_buf[t]=='0')
          bitmap[BM_CANVAS]->Canvas->Draw(t*bitmap[BM_NIC]->Height,level.cnt.y*bitmap[BM_NIC]->Height,bitmap[BM_NIC]);
          else
          if ((int)line_buf[t]=='1')
          bitmap[BM_CANVAS]->Canvas->Draw(t*bitmap[BM_NIC]->Height,level.cnt.y*bitmap[BM_NIC]->Height,bitmap[BM_MAPA]);

          level.mapka[t][level.cnt.y] = line_buf[t];
         }
      if (level.cnt.x < (int)strlen(line_buf))
          level.cnt.x = strlen(line_buf);
    }
plik_hnd.close();
plik_current.Name = a_plik_name;

  bitmap[BM_CANVAS]->Width = bitmap[BM_NIC]->Height * level.cnt.x;
MainForm->Left =  (Screen->Width - bitmap[BM_CANVAS]->Width)/2;
MainForm->ClientWidth = bitmap[BM_CANVAS]->Width;
 bitmap[BM_CANVAS]->Height = bitmap[BM_NIC]->Height * level.cnt.y;
 MainForm->Top = (Screen->Height - bitmap[BM_CANVAS]->Height)/2;
MainForm->ClientHeight = bitmap[BM_CANVAS]->Height + StatusBar1->Height;

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

void __fastcall TMainForm::Graj(void)
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
int nr;

randomize();
for (nr = 0; nr < gra.extra_cnt[ZB_ZBIER]; nr++)
    {
     do {
         gra.extra[ZB_ZBIER][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[ZB_ZBIER][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[ZB_ZBIER][0][nr]][gra.extra[ZB_ZBIER][1][nr]]!='0');

     gra.mapka[gra.extra[ZB_ZBIER][0][nr]][gra.extra[ZB_ZBIER][1][nr]]='2';
    }
for (nr = 0; nr < gra.extra_cnt[ZB_BONUS]; nr++)
    {
     do {
         gra.extra[ZB_BONUS][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[ZB_BONUS][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[ZB_BONUS][0][nr]][gra.extra[ZB_BONUS][1][nr]]!='0');

     gra.mapka[gra.extra[ZB_BONUS][0][nr]][gra.extra[ZB_BONUS][1][nr]]='3';
    }
for (nr = 0; nr < gra.extra_cnt[ZB_CLOCK]; nr++)
    {
     do {
         gra.extra[ZB_CLOCK][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[ZB_CLOCK][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[ZB_CLOCK][0][nr]][gra.extra[ZB_CLOCK][1][nr]]!='0');

     gra.mapka[gra.extra[ZB_CLOCK][0][nr]][gra.extra[ZB_CLOCK][1][nr]]='4';
    }
Repaint();

punktow = 0;
MainForm->Caption = "Grasz : 0 punkt�w w level \""+plik_current.Name+"\"";
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
    if (czas-czas_old < gra.reftime)
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

    if (im>=gra.waz_cnt)
       {gra.mapka[ruch[0][im-gra.waz_cnt]][ruch[1][im-gra.waz_cnt]]='0';
       }
    if (gra.mapka[ruch[0][im]][ruch[1][im]]=='1')
       {gram = false;
        stop = true;
        --im;
        return;
       }
    else gra.mapka[ruch[0][im]][ruch[1][im]]='1';

    if (im>0 && gra.waz_cnt>1)
       {MainForm->Canvas->Draw(ruch[0][im-1]*bitmap[BM_NIC]->Height,ruch[1][im-1]*bitmap[BM_NIC]->Height,bitmap[BM_KROPA]);
       }
    if (im>=gra.waz_cnt)
       {MainForm->Canvas->Draw(ruch[0][im-gra.waz_cnt]*bitmap[BM_NIC]->Height,ruch[1][im-gra.waz_cnt]*bitmap[BM_NIC]->Height,bitmap[BM_NIC]);
       }

    MainForm->Canvas->Draw(ruch[0][im]*bitmap[BM_NIC]->Height,ruch[1][im]*bitmap[BM_NIC]->Height,bitmap[BM_GLOWA]);

    if (gra.reftime > gra.ref_mul)
    gra.reftime = gra.reftime*(1 - gra.ref_mul);
    if (gra.igntime > gra.ign_mul)
    gra.igntime = gra.igntime*(1 - gra.ign_mul);

    czas_old = timeGetTime();

    if (gra.mov.x>0 ? gra.mapka[(int)ruch[0][im]+1][(int)ruch[1][im]+0]=='1' : false)
        czas_old+=gra.igntime;
    else
    if (gra.mov.x<0 ? gra.mapka[(int)ruch[0][im]-1][(int)ruch[1][im]+0]=='1' : false)
        czas_old+=gra.igntime;
    else
    if (gra.mov.y>0 ? gra.mapka[(int)ruch[0][im]+0][(int)ruch[1][im]+1]=='1' : false)
        czas_old+=gra.igntime;
    else
    if (gra.mov.y<0 ? gra.mapka[(int)ruch[0][im]+0][(int)ruch[1][im]-1]=='1' : false)
        czas_old+=gra.igntime;

   } while (stop==false);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Zbieraj(void)
{
if (gram==false)
    return;
int nr,zzz;
randomize();
for (nr = 0; nr < gra.extra_cnt[ZB_ZBIER]; nr++)
    {
     if ((int)ruch[0][im]!=(int)gra.extra[ZB_ZBIER][0][nr] || (int)ruch[1][im]!=(int)gra.extra[ZB_ZBIER][1][nr])
         continue;

     if (gra.reftime < level.reftime)
     gra.reftime = gra.reftime*(1 + gra.cnt.x*gra.ref_mul);
     if (gra.igntime < level.igntime)
     gra.igntime = gra.igntime*(1 + gra.cnt.x*gra.ign_mul);

     gra.waz_cnt++;
     punktow += int((100 * level.reftime) / gra.reftime);
     if (sound_exists)
         Sound("zbier.wav");

     MainForm->Canvas->Draw(gra.extra[ZB_ZBIER][0][nr]*bitmap[BM_NIC]->Height,gra.extra[ZB_ZBIER][1][nr]*bitmap[BM_NIC]->Height,bitmap[BM_NIC]);
     do {
         gra.extra[ZB_ZBIER][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[ZB_ZBIER][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[ZB_ZBIER][0][nr]][gra.extra[ZB_ZBIER][1][nr]]!='0');

      gra.mapka[gra.extra[ZB_ZBIER][0][nr]][gra.extra[ZB_ZBIER][1][nr]] = '2';
     MainForm->Canvas->Draw(gra.extra[ZB_ZBIER][0][nr]*bitmap[BM_NIC]->Height,gra.extra[ZB_ZBIER][1][nr]*bitmap[BM_NIC]->Height,bitmap[BM_ZBIER]);
    }
for (nr = 0; nr < gra.extra_cnt[ZB_CLOCK]; nr++)
    {
     if (im%gra.cnt.x==0) goto CLOCK_LOS_LABEL;
     else
     if ((int)ruch[0][im]!=(int)gra.extra[ZB_CLOCK][0][nr] || (int)ruch[1][im]!=(int)gra.extra[ZB_CLOCK][1][nr])
         continue;

     if (gra.reftime < level.reftime)
     gra.reftime = gra.reftime*(1 + gra.cnt.x*gra.ref_mul*5);
     if (gra.igntime < level.igntime)
     gra.igntime = gra.igntime*(1 + gra.cnt.x*gra.ign_mul*5);

     gra.waz_cnt+=5;

     punktow -= int(1*100);
     if (sound_exists)
         Sound("clock.wav");

CLOCK_LOS_LABEL:
     MainForm->Canvas->Draw(gra.extra[ZB_CLOCK][0][nr]*bitmap[BM_NIC]->Height,gra.extra[ZB_CLOCK][1][nr]*bitmap[BM_NIC]->Height,bitmap[BM_NIC]);
     do {
         gra.extra[ZB_CLOCK][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[ZB_CLOCK][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[ZB_CLOCK][0][nr]][gra.extra[ZB_CLOCK][1][nr]]!='0');

        gra.mapka[gra.extra[ZB_CLOCK][0][nr]][gra.extra[ZB_CLOCK][1][nr]] = '4';
     MainForm->Canvas->Draw(gra.extra[ZB_CLOCK][0][nr]*bitmap[BM_NIC]->Height,gra.extra[ZB_CLOCK][1][nr]*bitmap[BM_NIC]->Height,bitmap[BM_CLOCK]);
    }
for (nr = 0; nr < gra.extra_cnt[ZB_BONUS]; nr++)
    {
     if (im%(gra.cnt.x+gra.cnt.y)==0) goto BONUS_LOS_LABEL;
     else
     if ((int)ruch[0][im]!=(int)gra.extra[ZB_BONUS][0][nr] || (int)ruch[1][im]!=(int)gra.extra[ZB_BONUS][1][nr])
         continue;

     for (zzz = 0; zzz <= 5; zzz++)
         {
          if (gra.waz_cnt <= zzz)
              break;
          gra.mapka[ruch[0][im-gra.waz_cnt+zzz]][ruch[1][im-gra.waz_cnt+zzz]] = '0';
          MainForm->Canvas->Draw(ruch[0][im-gra.waz_cnt+zzz]*bitmap[BM_NIC]->Height,ruch[1][im-gra.waz_cnt+zzz]*bitmap[BM_NIC]->Height,bitmap[BM_NIC]);
         }
     if  (gra.waz_cnt<=5) gra.waz_cnt = 1;
     else gra.waz_cnt-=5;

     if (gra.reftime < level.reftime)
     gra.reftime = gra.reftime*(1 - gra.cnt.x*gra.ref_mul*5);
     if (gra.igntime < level.igntime)
     gra.igntime = gra.igntime*(1 - gra.cnt.x*gra.ign_mul*5);

     punktow -= int(1*100);
     if (sound_exists)
         Sound("bonus.wav");
BONUS_LOS_LABEL:
     MainForm->Canvas->Draw(gra.extra[ZB_BONUS][0][nr]*bitmap[BM_NIC]->Height,gra.extra[ZB_BONUS][1][nr]*bitmap[BM_NIC]->Height,bitmap[BM_NIC]);
     do {
         gra.extra[ZB_BONUS][0][nr] = int(rand() % gra.cnt.x);
         gra.extra[ZB_BONUS][1][nr] = int(rand() % gra.cnt.y);

        } while ((int)gra.mapka[gra.extra[ZB_BONUS][0][nr]][gra.extra[ZB_BONUS][1][nr]]!='0');

        gra.mapka[gra.extra[ZB_BONUS][0][nr]][gra.extra[ZB_BONUS][1][nr]] = '3';
     MainForm->Canvas->Draw(gra.extra[ZB_BONUS][0][nr]*bitmap[BM_NIC]->Height,gra.extra[ZB_BONUS][1][nr]*bitmap[BM_NIC]->Height,bitmap[BM_BONUS]);
    }
MainForm->Caption = "Grasz : "+(String)punktow+" punkt�w w levelu \""+plik_current.Name+"\"";
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormPaint(TObject *Sender)
{
Canvas->CopyRect(Canvas->ClipRect,bitmap[BM_CANVAS]->Canvas,Canvas->ClipRect);
int nr;
for (nr = 0; nr < gra.extra_cnt[ZB_CLOCK]; nr++)
    {MainForm->Canvas->Draw(gra.extra[ZB_CLOCK][0][nr]*bitmap[BM_NIC]->Height,gra.extra[ZB_CLOCK][1][nr]*bitmap[BM_NIC]->Height,bitmap[BM_CLOCK]);
    }
for (nr = 0; nr < gra.extra_cnt[ZB_BONUS]; nr++)
    {MainForm->Canvas->Draw(gra.extra[ZB_BONUS][0][nr]*bitmap[BM_NIC]->Height,gra.extra[ZB_BONUS][1][nr]*bitmap[BM_NIC]->Height,bitmap[BM_BONUS]);
    }
for (nr = 0; nr < gra.extra_cnt[ZB_ZBIER]; nr++)
    {MainForm->Canvas->Draw(gra.extra[ZB_ZBIER][0][nr]*bitmap[BM_NIC]->Height,gra.extra[ZB_ZBIER][1][nr]*bitmap[BM_NIC]->Height,bitmap[BM_ZBIER]);
    }
for (nr = 1; nr < gra.waz_cnt; nr++)
    {if (im>=nr)
         MainForm->Canvas->Draw(ruch[0][im-nr]*bitmap[BM_NIC]->Height,ruch[1][im-nr]*bitmap[BM_NIC]->Height,bitmap[BM_KROPA]);
    }
 if (gra.waz_cnt > 0)
     MainForm->Canvas->Draw(ruch[0][im]*bitmap[BM_NIC]->Height,ruch[1][im]*bitmap[BM_NIC]->Height,bitmap[BM_GLOWA]);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::OpcjeClick(TObject *Sender)
{
OpcjeForm->UpDown1->Position = level.waz_cnt;
OpcjeForm->UpDown2->Position = level.reftime;
OpcjeForm->UpDown3->Position = level.extra_cnt[ZB_ZBIER];

OpcjeForm->ShowModal();

level.extra_cnt[ZB_ZBIER] = OpcjeForm->UpDown3->Position;
   level.reftime = OpcjeForm->UpDown2->Position;
level.waz_cnt = OpcjeForm->UpDown1->Position;

OpcjeForm->Edit3->Text = level.extra_cnt[ZB_ZBIER];
OpcjeForm->Edit2->Text = level.reftime;
OpcjeForm->Edit1->Text = level.waz_cnt;
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::PauzaClick(TObject *Sender)
{
if (stop==true)
    return;
pauza=!pauza;
if (sound_exists)
    Sound("pauza.wav");
if (pauza==true) MainForm->Caption = "Pauza : " + (String)punktow + " punkt�w w levelu \""+plik_current.Name+"\"";
else MainForm->Caption = "Grasz : " + (String)punktow + " punkt�w w levelu \""+plik_current.Name+"\"";
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
if (sound_exists) Sound("stop.wav");
MainForm->Caption = "Koniec : "+(String)punktow+" punkt�w w levelu "+plik_current.Name;
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
About_form->ShowModal();
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
mapa = 1;
Load(plik[1].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N21Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 2;
Load(plik[2].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N31Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 3;
Load(plik[3].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N41Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 4;
Load(plik[4].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N51Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 5;
Load(plik[5].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N61Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 6;
Load(plik[6].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N71Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 7;
Load(plik[7].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N81Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 8;
Load(plik[8].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N91Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 9;
Load(plik[9].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N101Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 10;
Load(plik[10].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::N111Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 11;
Load(plik[11].Name);
}
//---------------------------------------------------------------------------
void __fastcall TMainForm::N121Click(TObject *Sender)
{
if (gram==true)
    return;
mapa = 12;
Load(plik[12].Name);
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::StartClick(TObject *Sender)
{
if (plik_current.Index!=0 && mapa!=0) Graj();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::FormShow(TObject *Sender)
{
static bool first_time = true;
if (!first_time)
return;

first_time = false;
	  gram = false;
	 pauza = false;
	  stop = true;

bitmap[BM_CANVAS]->Height = 1024;
 bitmap[BM_CANVAS]->Width = 2048;
bitmap[BM_CANVAS]->LoadFromResourceName((int)hInst,"LOGO");

 bitmap[BM_KROPA]->LoadFromFile("kropa.bmp");
 bitmap[BM_GLOWA]->LoadFromFile("glowa.bmp");
   bitmap[BM_NIC]->LoadFromFile("nic.bmp");
 bitmap[BM_ZBIER]->LoadFromFile("zbier.bmp");
 bitmap[BM_BONUS]->LoadFromFile("bonus.bmp");
 bitmap[BM_CLOCK]->LoadFromFile("clock.bmp");
  bitmap[BM_MAPA]->LoadFromFile("mapa.bmp");

setmem(&level,sizeof(level),0x00);
Levele();
MainForm->Repaint();
}
//---------------------------------------------------------------------------

void __fastcall TMainForm::Mapka2Click(TObject *Sender)
{
Form1->ShowModal();
}
//---------------------------------------------------------------------------



