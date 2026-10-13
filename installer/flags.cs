using System;
using System.Drawing;
using System.Drawing.Drawing2D;
public static class VisorFlags {
 static PointF[] Star(float x,float y,float radius,int points) {
  PointF[] result=new PointF[points*2];
  for(int i=0;i<result.Length;i++){double a=-Math.PI/2+i*Math.PI/points;float r=(i%2==0)?radius:radius*0.42f;result[i]=new PointF(x+(float)Math.Cos(a)*r,y+(float)Math.Sin(a)*r);}
  return result;
 }
 public static Bitmap Create(string code) {
  Bitmap b=new Bitmap(24,16);
  using(Graphics g=Graphics.FromImage(b)) {
   g.Clear(Color.White);g.SmoothingMode=SmoothingMode.AntiAlias;
   if(code=="ru-RU"||code=="de-DE") {
    g.FillRectangle(code=="ru-RU"?Brushes.White:Brushes.Black,0,0,24,5.34f);
    g.FillRectangle(code=="ru-RU"?Brushes.RoyalBlue:Brushes.Red,0,5.33f,24,5.34f);
    g.FillRectangle(code=="ru-RU"?Brushes.Red:Brushes.Gold,0,10.66f,24,5.34f);
   } else if(code=="fr-FR") {
    g.FillRectangle(Brushes.RoyalBlue,0,0,8,16);g.FillRectangle(Brushes.Red,16,0,8,16);
   } else if(code=="es-ES") {
    g.Clear(Color.Red);g.FillRectangle(Brushes.Gold,0,4,24,8);g.FillRectangle(Brushes.DarkRed,6,6,2,4);
   } else if(code=="en-US") {
    for(int i=0;i<13;i+=2)g.FillRectangle(Brushes.Firebrick,0,i*16f/13,24,16f/13);
    g.FillRectangle(Brushes.MidnightBlue,0,0,10,9);
    for(int y=1;y<8;y+=2)for(int x=1;x<10;x+=2)g.FillEllipse(Brushes.White,x,y,0.8f,0.8f);
   } else if(code=="pt-BR") {
    g.Clear(Color.ForestGreen);g.FillPolygon(Brushes.Gold,new PointF[]{new PointF(12,1),new PointF(23,8),new PointF(12,15),new PointF(1,8)});
    g.FillEllipse(Brushes.RoyalBlue,7,3,10,10);g.DrawArc(Pens.White,6,6,12,8,200,140);
   } else if(code=="ja-JP") {
    g.FillEllipse(Brushes.Crimson,8,4,8,8);
   } else if(code=="ko-KR") {
    g.FillEllipse(Brushes.Crimson,8,4,8,8);g.FillPie(Brushes.RoyalBlue,8,4,8,8,0,180);
    g.FillEllipse(Brushes.Crimson,8,6,4,4);g.FillEllipse(Brushes.RoyalBlue,12,6,4,4);
    for(int i=0;i<3;i++){g.DrawLine(Pens.Black,3,2+i,6,2+i);g.DrawLine(Pens.Black,18,11+i,21,11+i);g.DrawLine(Pens.Black,18,2+i,19,2+i);g.DrawLine(Pens.Black,20,2+i,21,2+i);g.DrawLine(Pens.Black,3,11+i,4,11+i);g.DrawLine(Pens.Black,5,11+i,6,11+i);}
   } else if(code=="zh-CN") {
    g.Clear(Color.Red);g.FillPolygon(Brushes.Gold,Star(4.5f,4.5f,2.5f,5));
    foreach(PointF p in new PointF[]{new PointF(8,2),new PointF(10,4),new PointF(10,6),new PointF(8,8)})g.FillPolygon(Brushes.Gold,Star(p.X,p.Y,0.8f,5));
   } else if(code=="zh-TW") {
    g.Clear(Color.Red);g.FillRectangle(Brushes.MidnightBlue,0,0,12,8);g.FillPolygon(Brushes.White,Star(6,4,3,12));g.FillEllipse(Brushes.MidnightBlue,4,2,4,4);g.FillEllipse(Brushes.White,4.4f,2.4f,3.2f,3.2f);
   }
   g.DrawRectangle(Pens.Gray,0,0,23,15);
  }
  return b;
 }
}
