struct WesImageWatchRGB {
  unsigned int nBitCount;	//8/32
  unsigned int nWidth;
  unsigned int nHeight;
  unsigned int nPitch;
  unsigned char* pData;
  WesImageWatchRGB()
  {
    nWidth = nHeight = nPitch = 0; pData = nullptr; nBitCount = 32;
  }
};

struct WesImageWatchYV12
{
  unsigned int ncols;
  unsigned int nrows;
  unsigned int ypitch;
  unsigned int upitch;
  unsigned int vpitch;
  unsigned char* ydata;
  unsigned char* udata;
  unsigned char* vdata;
  WesImageWatchYV12()
  {
    ncols = nrows = ypitch = upitch = vpitch = 0;
    ydata = udata = vdata = nullptr;
  }
};
