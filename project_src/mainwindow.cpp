#include "mainwindow.h"
#include "ui_mainwindow.h"

double ftk(1.78), fck(16.7) , afaA(2.19) , afaD(0.52) , afaT(1.052) ;
int fyk(300) , e0(1404) , et0(-90) ;
int H0(460) ,b(250) , H(500) ,ap(40) ,a(40);
double As(0) , Asp(0) ;
double Mmax = 0;
double Mcr = 0;
float yt = 0,dety= H;
int maxfai = 0;
int mcrfai = 0;
int myfai = 0;
double My = 0;
int Hp;
bool qufux = 1;
QString MCR;

QString MAX;

QString MY;


void MainWindow::paintEvent(QPaintEvent *event){

    QPainter p(this);
    p.translate(320,440);
    p.scale(1,-1);
    QPen pen1(Qt::black,1);
    p.setPen(pen1);
    p.drawLine(0,0,820,0);
    p.drawLine(200,0,200,3);
    p.drawLine(400,0,400,3);
    p.drawLine(600,0,600,3);
    p.drawLine(800,0,800,3);
    p.drawLine(0,0,0,410);
    QPen pen2(Qt::red,4);
    QPen pen3(Qt::blue,3);
    QPen pen4(Qt::black,40);
    if(Mx[0] == 1){

        p.setPen(pen2);  //选择画笔
           p.scale(0.1,0.1);

        for(int i = 1;i<=4000;++i){
            p.drawLine(2*(i-1),4000*Mx[i-1]/Mmax,2*i,4000*Mx[i]/Mmax);
        }
        p.setPen(pen3);
         p.drawLine(2*maxfai,4000,0,4000);
         p.drawLine(2*mcrfai,Mcr*4000/Mmax,0,Mcr*4000/Mmax);
        p.setPen(pen4);
         p.drawPoint(2*maxfai,4000); p.drawPoint(2*mcrfai,Mcr*4000/Mmax);
         if(My != 0 && As != 0)    p.drawPoint(2*myfai,My*4000/Mmax);
         p.scale(10,10);
         p.scale(1,-1);

         p.drawText( maxfai/5-4,-405,"Mu");
         p.drawText( mcrfai/5+5,-Mcr*400/Mmax + 5,"Mcr");
         if(As!=0&&My!=0) p.drawText( myfai/5-4,-My*400/Mmax + 15,"My");


        //用该红色画笔画一条线，起点(0,0)，终点(100,100)
    }
}

double fy(double e){
    if(e >= -5*fyk && e <= 5*fyk)
    return e/5;
    else if(e < -5*fyk)
    return -fyk;
    else  return fyk;
}

double cigma(double e){
    double x1= e/e0;
    double x2 = e/et0;
    if(e >= 0 && e <= e0)
    return (afaA*x1 + (3-2*afaA)*x1*x1 + (afaA-2)*x1*x1*x1)*fck;
    else if(e > e0)
    return (x1/(afaD*(x1-1)*(x1-1) + x1))*fck;
    else if(e < 0 && e >= et0)
    return (-1.2*x2+0.2*x2*x2*x2*x2*x2*x2)*ftk;
    else return(-x2/(afaT*pow(x2 - 1,1.7)+x2));
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
    {
    ui->setupUi(this);

    ui->AsBox->setMaximum(50000);
    ui->AspBox->setMaximum(50000);
    ui->hBox->setMaximum(2000);
    ui->hBox->setValue(500);
    ui->bBox->setMaximum(2000);
    ui->bBox->setValue(250);
    ui->aBox->setMaximum(1000);
    ui->aBox->setValue(40);
    ui->apBox->setMaximum(1000);
    ui->apBox->setValue(40);

    }



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    Mx[0] = 0;
    Mmax = 0;
    Mcr = 0;
    My = 0;
    maxfai = 0;
    mcrfai = 0;
    myfai = 0;
    Mx[0] = 1;
    qufux = 1;
    dety = 500;
    H0 = H - a;
    int fai;
    float ecu = 0;
    float h1,h2,deth,hx;
    float M ;
    float N;
    float ey;
    for(fai =1;fai<=4000;fai=fai +1){
        M = 0;
        h1 = 0;
        hx = H0/2;
        h2 = H0;
        deth = H0;
        while(deth > 0.1){
            N = 0;
            ecu = fai*hx/100;
            for (int y=0; y<H; y = y=y+1){
                ey = ecu - (y+0.05)*fai/100;
                if (ey<et0)  break;
                N = N + cigma(ey);
            }
            N = N*b + fy(ecu - H0*fai/100)*As + fy(ecu - ap*fai/100)*Asp;



            if(N>=0)  h2 = hx;
            else  h1 = hx;
            hx = (h1 + h2)/2;
            deth = deth/2;
        }
        Hp = 10*H;
        for (int y=0; y<Hp; y =y+ 1){
                ey = ecu - y*fai/1000 - fai/2000;

                if(ey < et0)  {
                    yt = y/10;
                    break;
                }

                M = M + cigma(ey)*b*(y+0.5)/100;
            }

        for (int y=yt; y<H; y = y + 1){
                ey = ecu - (y+0.5)*fai/100;
                M = M + cigma(ey)*b*0.1*(y+0.5);
            }

        M = -M - fy(ecu-fai*H0/100)*As*H0 - fy(ecu-fai*ap/100)*Asp*ap;

        Mx[fai] = M/1000000;

        if(dety > H - yt)  {
            dety = H - yt;
            mcrfai = fai - 1;
            Mcr = Mx[fai -1];
        }

        if(qufux == 1 && fy(ecu-fai*H0/100)== -fyk){
            qufux = 0;
            myfai = fai;
            My = Mx[fai];

        }

        if(Mmax <= Mx[fai]) {
            Mmax = Mx[fai];
            maxfai = fai;}
    }


    MAX = QString::number(Mmax);
    MCR = QString::number(Mcr);
    MY = QString::number(My);
    ui->textBrowserM->setText(MAX);
    if(As == 0 or My == 0)    ui->textBrowserMy->setText("不屈服");
    else ui->textBrowserMy->setText(MY);
    ui->textBrowserMCR->setText(MCR);
    ui->labelhM->setText("(Mu = "+MAX+" KN*m)");
    repaint();
}



void MainWindow::on_AsBox_valueChanged(double arg1)
{
    As = arg1;
}

void MainWindow::on_cocBox_currentTextChanged(const QString &arg1)
{
    if(arg1 == "C25")  ftk=1.78, fck=16.7, afaA=2.19 , afaD=0.52 , afaT=1.052, e0=1404 , et0=-90;
    else if(arg1 == "C30")  ftk=2.01, fck=20.1, afaA=2.15 , afaD=0.74 , afaT=1.25, e0=1471 , et0=-95;
    else if(arg1 == "C35")  ftk=2.20, fck=23.4, afaA=2.11 , afaD=0.96 , afaT=1.53, e0=1531 , et0=-100;
    else if(arg1 == "C40")  ftk=2.39, fck=26.8, afaA=2.07 , afaD=1.17 , afaT=1.796, e0=1579 , et0=-105;
    else if(arg1 == "C45")  ftk=2.51, fck=29.6, afaA=2.03 , afaD=1.35 , afaT=1.97, e0=1647 , et0=-107;
    else if(arg1 == "C50")  ftk=2.64, fck=32.4, afaA=2 , afaD=1.5 , afaT=2.19, e0=1679 , et0=-110;
    else if(arg1 == "C55")  ftk=2.74, fck=35.5, afaA=1.96 , afaD=1.66 , afaT=2.363, e0=1724 , et0=-112;
    else if(arg1 == "C60")  ftk=2.85, fck=38.5, afaA=1.92 , afaD=1.85 , afaT=2.552, e0=1769 , et0=-115;
    else if(arg1 == "C65")  ftk=2.93, fck=41.5, afaA=1.88 , afaD=2.02 , afaT=2.69, e0=1808 , et0=-117;
    else if(arg1 == "C70")  ftk=2.99, fck=44.5, afaA=1.84 , afaD=2.19 , afaT=2.8, e0=1847 , et0=-118;
    else if(arg1 == "C75")  ftk=3.05, fck=47.4, afaA=1.81 , afaD=2.34 , afaT=2.91, e0=1884 , et0=-119;
    else if(arg1 == "C80")  ftk=3.11, fck=50.2, afaA=1.78 , afaD=2.49 , afaT=3.03, e0=1921 , et0=-120;
}

void MainWindow::on_steelBox_currentTextChanged(const QString &arg1)
{
     if(arg1 == "HRB300")  fyk = 300;
     else if(arg1 == "HRB335")  fyk = 335;
     else if(arg1 == "HRB400")  fyk = 400;
     else if(arg1 == "HRB500")  fyk = 500;
}

void MainWindow::on_AspBox_valueChanged(double arg1)
{
    Asp = arg1;
}

void MainWindow::on_hBox_valueChanged(double arg1)
{
    H = arg1;
}

void MainWindow::on_bBox_valueChanged(double arg1)
{
    b = arg1;
}

void MainWindow::on_aBox_valueChanged(double arg1)
{
    a = arg1;
}

void MainWindow::on_apBox_valueChanged(double arg1)
{
    ap = arg1;
}


void MainWindow::on_pushButton_clicked()
{
    ui->textBrowserM->setText("");
    ui->textBrowserMCR->setText("");
    ui->textBrowserMy->setText("");
    Mx[0] = 0;
    ui->labelhM->setText("");
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    QApplication::exit();
}
