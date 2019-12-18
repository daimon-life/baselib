
// libsamplerate
// http://www.linuxfromscratch.org/blfs/view/cvs/multimedia/libsamplerate.html
// http://www.mega-nerd.com/SRC/libsamplerate-0.1.9.tar.gz
// https://github.com/erikd/libsamplerate
int ResampleS16le(int iiRate, short* pIn, int iLen, int oiRate, short* pOut, int* poLen)
{
		double dRatio = oiRate*1.0 / iiRate;
		int oLenPre = (int)(dRatio*iLen) + 10;
		float* pOutflt = new float[oLenPre];
		float* pInflt = new float[iLen];
		src_short_to_float_array(pIn, pInflt, iLen);

		SRC_STATE* src_state = NULL;
		int error = -1;

		src_state = src_new(SRC_LINEAR, 1, &error);
		SRC_DATA src_data = { 0 };
		src_data.src_ratio = 1.0*oiRate / iiRate;
		src_data.data_in = pInflt;
		src_data.input_frames = iLen;
		src_data.data_out = pOutflt;                 
		src_data.output_frames = oLenPre;
		src_data.end_of_input = 0;
		error = src_process(src_state, &src_data);
		*poLen = src_data.output_frames_gen;
		src_delete(src_state);

		src_float_to_short_array(pOutflt, pOut, *poLen);
		delete[] pOutflt;
		delete[] pInflt;

		return 0;
}
  
// libsndfile 
// http://www.linuxfromscratch.org/blfs/view/cvs/multimedia/libsndfile.html
// http://www.mega-nerd.com/libsndfile/files/libsndfile-1.0.28.tar.gz
// https://github.com/erikd/libsndfile.git
// http://www.mega-nerd.com/libsndfile/#Download
void pcm_to_wav()
{
	std::fstream fAudioFile;
	fAudioFile.open("10_1channel_s16_44_1khz.pcm", std::fstream::in | std::fstream::binary);
	assert(fAudioFile.is_open());

	SF_INFO file_info;
	file_info.samplerate = 44100;
	file_info.channels   = 1;
	file_info.format     = SF_FORMAT_WAV | SF_FORMAT_PCM_16;
	SNDFILE* sndfile     = sf_open("./10_1channel_s16_44_1khz.wav", SFM_WRITE, &file_info);

	int    iPcmSize = 2 * 256;
	short* pPcmData = (short*)malloc(iPcmSize);

	do
	{
		fAudioFile.read((char*)pPcmData, iPcmSize);
		int iReadSize = fAudioFile.gcount();
		sf_write_short(sndfile, (short *)pPcmData, (sf_count_t)(iReadSize / sizeof(short)));
	} while (!fAudioFile.eof());

	sf_close(sndfile);
	fAudioFile.close();
}
