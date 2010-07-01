#include "video_codec/Mcodec.h"
#include "video_codec/Image.h"

int main ()
{
  Mcodec test;
  VideoCodec               VC;
  Image                    infos;

  infos = test.compressImage("/media/local_/Images/ipod/100APPLE/IMG_0007.JPG");
  VC.SaveImgInList(infos.getTab(),infos.getWidth(),infos.getHeight());
  infos = test.compressImage("/media/local_/Images/ipod/100APPLE/IMG_0007.JPG");
  VC.SaveImgInList(infos.getTab(),infos.getWidth(),infos.getHeight());
  infos = test.compressImage("/media/local_/Images/ipod/100APPLE/IMG_0007.JPG");
  VC.SaveImgInList(infos.getTab(),infos.getWidth(),infos.getHeight());
  infos = test.compressImage("/media/local_/Images/ipod/100APPLE/IMG_0007.JPG");
  VC.SaveImgInList(infos.getTab(),infos.getWidth(),infos.getHeight());
  infos = test.compressImage("/media/local_/Images/ipod/100APPLE/IMG_0007.JPG");
  VC.SaveImgInList(infos.getTab(),infos.getWidth(),infos.getHeight());
  infos = test.compressImage("/media/local_/Images/ipod/100APPLE/IMG_0007.JPG");
  VC.SaveImgInList(infos.getTab(),infos.getWidth(),infos.getHeight());
  infos = test.compressImage("/media/local_/Images/ipod/100APPLE/IMG_0007.JPG");
  VC.SaveImgInList(infos.getTab(),infos.getWidth(),infos.getHeight());
  infos = test.compressImage("/media/local_/Images/ipod/100APPLE/IMG_0007.JPG");
  VC.SaveImgInList(infos.getTab(),infos.getWidth(),infos.getHeight());
  infos = test.compressImage("/media/local_/Images/ipod/100APPLE/IMG_0007.JPG");
  VC.SaveImgInList(infos.getTab(),infos.getWidth(),infos.getHeight());


  VC.createFile("test.GuiGuy");
  VC.SaveFlux();
  VC.compression();
  VC.decompression();

  VC.lectureFichier();
  //      test.uncompressImage();                                                                                                                                                                          

  return 0;
 }
