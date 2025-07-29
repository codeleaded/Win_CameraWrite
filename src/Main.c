#include "/home/codeleaded/System/Static/Library/WindowEngine1.0.h"
#include "/home/codeleaded/System/Static/Library/RLCamera.h"
#include "/home/codeleaded/System/Static/Library/ImageFilter.h"


RLCamera rlc;
ORLCamera orlc;

Sprite sp;
float Regler1 = 0.5f;
float Regler2 = 0.5f;
int Mode = 0;

void Setup(AlxWindow* w){
    rlc = RLCamera_New("/dev/video0",RLCAMERA_WIDTH * 2,RLCAMERA_HEIGHT * 2);
    orlc = ORLCamera_New("/dev/video10",RLCAMERA_WIDTH * 2,RLCAMERA_HEIGHT * 2);

    //RLCamera_JPEG_Save(&rlc,"Bild.jpg");
    //window.Running = 0;
}

void Update(AlxWindow* w){

    if(Stroke(ALX_KEY_0).PRESSED) Mode = 0;
	if(Stroke(ALX_KEY_1).PRESSED) Mode = 1;
	if(Stroke(ALX_KEY_2).PRESSED) Mode = 2;
	if(Stroke(ALX_KEY_3).PRESSED) Mode = 3;
	if(Stroke(ALX_KEY_4).PRESSED) Mode = 4;
	if(Stroke(ALX_KEY_5).PRESSED) Mode = 5;
	if(Stroke(ALX_KEY_6).PRESSED) Mode = 6;
	if(Stroke(ALX_KEY_7).PRESSED) Mode = 7;
	if(Stroke(ALX_KEY_8).PRESSED) Mode = 8;
	if(Stroke(ALX_KEY_9).PRESSED) Mode = 9;
	if(Stroke(ALX_KEY_R).PRESSED) Mode = 10;
	if(Stroke(ALX_KEY_T).PRESSED) Mode = 11;
	if(Stroke(ALX_KEY_Z).PRESSED) Mode = 12;
	if(Stroke(ALX_KEY_U).PRESSED) Mode = 13;
	if(Stroke(ALX_KEY_I).PRESSED) Mode = 14;

	if(Stroke(ALX_KEY_W).DOWN) Regler1 *= 1.01;
	if(Stroke(ALX_KEY_S).DOWN) Regler1 *= 0.99;
	if(Stroke(ALX_KEY_E).DOWN) Regler2 *= 1.01;
	if(Stroke(ALX_KEY_D).DOWN) Regler2 *= 0.99;
    
    Sprite now = Sprite_None();
    int width = 0,height = 0;
    now.img = RLCamera_Get(&rlc,&width,&height);
    now.w = width;
    now.h = height;
    
    Clear(BLACK);

    if(now.img){
        Sprite_Render(WINDOW_STD_ARGS,&sp,0.0f,0.0f);

        Sprite trans = Sprite_None();
        if(Mode==0){
            Sprite_Render(WINDOW_STD_ARGS,&sp,0.0f,0.0f);
        }else if(Mode==1){
            trans = ImageFilter_BW_LRGB(&sp,Regler1);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==2){
            trans = ImageFilter_BW_LN(&sp,Regler1);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==3){
            trans = ImageFilter_G(&sp);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==4){
            trans = ImageFilter_G_ImageKernel3x3(&sp,ImageKernel3x3_Blur());
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==5){
            trans = ImageFilter_G_ImageKernel3x3(&sp,ImageKernel3x3_Sharpen());
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==6){
            trans = ImageFilter_G_ImageKernel3x3(&sp,ImageKernel3x3_Sobel_V());
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==7){
            trans = ImageFilter_G_ImageKernel3x3(&sp,ImageKernel3x3_Sobel_H());
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==8){
            trans = ImageFilter_BW_Morpho_Dilation(&sp,Regler1);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==9){
            trans = ImageFilter_BW_Morpho_Erosion(&sp,Regler1);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==10){
            trans = ImageFilter_BW_Morpho_Edge(&sp,Regler1);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==11){
            trans = ImageFilter_G_Median(&sp);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==12){
            trans = ImageFilter_G_Adaptive(&sp,Regler1);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==13){
            trans = ImageFilter_C_Motion(&sp,&now,Regler1);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }else if(Mode==14){
            trans = ImageFilter_G_TemporalRC(&sp,&now,Regler1);
            Sprite_Render(WINDOW_STD_ARGS,&trans,0.0f,0.0f);
        }

        String str = String_Format("Info: %d -> %f, %f",Mode,Regler1,Regler2);
	    CStr_RenderSizeAlxFont(WINDOW_STD_ARGS,&window.AlxFont,str.Memory,str.size,0.0f,0.0f,RED);
	    String_Free(&str);

        ORLCamera_Set(&orlc,trans.img,trans.w,trans.h);

        Sprite_Free(&trans);
        Sprite_Free(&sp);
        sp = now;
    }

    //RLCamera_JPEG_Save(&rlc,"Bild.jpg");
}

void Delete(AlxWindow* w){
    RLCamera_Free(&rlc);
    ORLCamera_Free(&orlc);
}

int main(){
    if(Create("Camera Test",1600,1000,1,1,Setup,Update,Delete))
        Start();
    return 0;
}