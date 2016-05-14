#include "opencv2/imgproc.hpp"
#include "opencv2/core.hpp"
#include "opencv2/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

int main( int argc, char** argv )
{

	Mat src, src_gray;
  	Mat dst, cdst;
  	int i;

  	//Le a imagem 
  	src = imread( argv[1] );
  	cdst = imread( argv[1] );
  	if( !src.data ){ 
  		return -1; 
  	}

  	//Converte para grayscale
  	cvtColor( src, src_gray, COLOR_RGB2GRAY );
  	//tira o ruido
  	blur(src_gray, src_gray, Size(3,3) );
  	//aplica o Canny para detectar as bordas
  	Canny(src_gray, dst, 50, 150, 3);

  	std::vector<Vec2f> lines;
  	//aplica Hough e detecta as linhas na imagem
  	HoughLines(dst, lines, 1, CV_PI/180, 100, 0, 0 );

  	//Para cada linha detectada temos que tratar manualmente para 
  	//pegar as linhas desejadas
  	for(i = 0; i < lines.size(); i++ )
  	{
		//Calcula dois pontos pertencentes a reta encontrada	
		float rho = lines[i][0], theta = lines[i][1];
    	Point pt1, pt2;
     	double a = cos(theta), b = sin(theta);
     	double x0 = a*rho, y0 = b*rho;
     	pt1.x = cvRound(x0 + 1000*(-b));
     	pt1.y = cvRound(y0 + 1000*(a));
     	pt2.x = cvRound(x0 - 1000*(-b));
     	pt2.y = cvRound(y0 - 1000*(a));

     	//calcula o angulo da reta para saber sua orientacao
     	double angle = atan2(pt2.y - pt1.y, pt2.x - pt1.x) * 180.0 / CV_PI;
     	
     	if(angle == 0){
     		if(pt1.y == 69 || pt1.y == 92 || pt1.y == 437 || pt1.y == 481){
     			line(cdst, pt1, pt2, Scalar(0,0,255),2, CV_AA, 0);
     		}
     		if(pt1.y == 132 || pt1.y == 167 || pt1.y == 205 || pt1.y == 245 
     			|| pt1.y == 288|| pt1.y == 334 || pt1.y == 383){
     			line(cdst, pt1, pt2, Scalar(0,255,0),2, CV_AA, 0);
     		}
     	}else if (angle >= 35 && angle <= 145){
     		if(pt2.x == 612 || pt2.x == 513 || pt2.x == 706){
     			line(cdst, pt1, pt2, Scalar(255,0,0),2, CV_AA, 0);
     		}
     		if(pt2.x == 800 || pt2.x == 876){
     			line(cdst, pt1, pt2, Scalar(0,0,255),2, CV_AA, 0);
     		}
     		
     	}else if(angle <= -25 && angle >= -165){
     		if(pt2.x == 374 || pt2.x == 372 || pt2.x == 391 || (pt2.x == 396 && pt1.y == 1000)){
     			line(cdst, pt1, pt2, Scalar(255,0,0),2, CV_AA, 0);
     		}
     		if(pt2.x == 375 || pt2.x == 383){
     			line(cdst, pt1, pt2, Scalar(0,0,255),2, CV_AA, 0);
     		}

     	}
  	}

	/* 	
 	if(!src.empty()){
    	imshow("source", src);
    }
 	if(!cdst.empty()){
    	imshow("detected lines",cdst);
 	}

 	waitKey();
	*/

  	imwrite(argv[2], cdst);	


  return 0;
 }