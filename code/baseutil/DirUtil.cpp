void CGoogleCloud::LoadAudio()
{
#if defined(WIN32) || defined(WIN64)
	WIN32_FIND_DATAA stFindFileData;
	HANDLE hFind = FindFirstFileA("./*.wav", &stFindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
		return;
	do 
	{
		if (stFindFileData.dwFileAttributes == FILE_ATTRIBUTE_NORMAL ||
			stFindFileData.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE ||
			stFindFileData.dwFileAttributes == FILE_ATTRIBUTE_HIDDEN ||
			stFindFileData.dwFileAttributes == FILE_ATTRIBUTE_SYSTEM ||
			stFindFileData.dwFileAttributes == FILE_ATTRIBUTE_READONLY) 
		{
			std::string szAudioFile = stFindFileData.cFileName;
			if (szAudioFile.size() == 36)
			{
				m_audioList.push_back(szAudioFile);
			}
		}
	} while (FindNextFileA(hFind, &stFindFileData));
	FindClose(hFind);
#endif

#if defined(__linux__) || defined(__APPLE__)
	DIR* dp;
	struct dirent* dirp;
	if ((dp = opendir("./")) == NULL)
		return;

	while ((dirp = readdir(dp)) != NULL) 
	{
		if (dirp->d_type == DT_REG) 
		{
			if (std::string(dirp->d_name).find("*.wav") != std::string::npos)
			{
				std::string szAudioFile = dirp->d_name;
				m_audioList.push_back(szAudioFile);
			}
		}
	}
	closedir(dp);
#endif
}


namespace Dir {

	class Directory {
	public:
		std::vector<std::string> GetListFiles(const std::string& path, const std::string & exten = "*", bool addPath = true);
		std::vector<std::string> GetListFilesR(const std::string& path, const std::string & exten = "*", bool addPath = true);
		std::vector<std::string> GetListFolders(const std::string& path, const std::string & exten = "*", bool addPath = true);
	};

	std::vector<std::string> Directory::GetListFiles(const std::string& path, const std::string & exten, bool addPath) {
		std::vector<std::string> list;
		list.clear(); 

#ifdef WIN32 
		std::string path_f = path + "/" + exten;
		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind = FindFirstFileA((LPCSTR)path_f.c_str(), &FindFileData);
		if (hFind == INVALID_HANDLE_VALUE) {
			return list;
		}
		else {
			do {
				if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_NORMAL ||
						FindFileData.dwFileAttributes == FILE_ATTRIBUTE_ARCHIVE ||
						FindFileData.dwFileAttributes == FILE_ATTRIBUTE_HIDDEN ||
						FindFileData.dwFileAttributes == FILE_ATTRIBUTE_SYSTEM ||
						FindFileData.dwFileAttributes == FILE_ATTRIBUTE_READONLY) {
					char* fname = FindFileData.cFileName;
					if (addPath) 
						list.push_back(path + "/" + std::string(fname)); 
					else 
						list.push_back(std::string(fname));
				}
			}
			while (FindNextFileA(hFind, &FindFileData));

			FindClose(hFind);
		}
#else 
		(void)addPath;
		DIR *dp;
		struct dirent *dirp;
		if (( dp = opendir(path.c_str()) ) == NULL) {
			return list;
		}

		while (( dirp = readdir(dp) ) != NULL) {
			if (dirp->d_type == DT_REG) {
        if (std::string(dirp->d_name).find(exten) != std::string::npos)
          list.push_back(static_cast<std::string>( dirp->d_name ));
			}
		}
		closedir(dp);
#endif
		return list;
	}

	std::vector<std::string> Directory::GetListFolders(const std::string& path, const std::string & exten, bool addPath) {
		std::vector<std::string> list; 
		std::string path_f = path + "/" + exten;
		list.clear();

#ifdef WIN32 
		WIN32_FIND_DATAA FindFileData;
		HANDLE hFind = FindFirstFileA((LPCSTR)path_f.c_str(), &FindFileData);

		if (hFind == INVALID_HANDLE_VALUE) {
			return list;
		} else {

			do {
				if (FindFileData.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY &&
						strcmp(FindFileData.cFileName, ".") != 0 && 
						strcmp(FindFileData.cFileName, "..") != 0)
				{
					char* fname = FindFileData.cFileName;

					if (addPath)
						list.push_back(path + "/" + std::string(fname));
					else
						list.push_back(std::string(fname));
				}
			}
			while (FindNextFileA(hFind, &FindFileData));
			FindClose(hFind);
		}
#else 
		(void)addPath;
		DIR *dp;
		struct dirent *dirp;
		if (( dp = opendir(path_f.c_str()) ) == NULL) {
			return list;
		}

		while (( dirp = readdir(dp) ) != NULL) {
			if (dirp->d_type == DT_DIR &&
					strcmp(dirp->d_name, ".") != 0 &&
					strcmp(dirp->d_name, "..") != 0) {
				if (exten.compare("*") == 0)
					list.push_back(static_cast<std::string>( dirp->d_name ));
				else if (std::string(dirp->d_name).find(exten) != std::string::npos)
					list.push_back(static_cast<std::string>( dirp->d_name ));
			}
		}
		closedir(dp);
#endif 

		return list;
	}

	std::vector<std::string> Directory::GetListFilesR(const std::string& path, const std::string & exten, bool addPath) {
		std::vector<std::string> list = Directory::GetListFiles(path, exten, addPath);
		std::vector<std::string> dirs = Directory::GetListFolders(path, "*", addPath);
		for (auto it = dirs.begin(); it != dirs.end(); ++it) {
			std::vector<std::string> cl = Directory::GetListFilesR(*it, exten, addPath);
			list.insert(list.end(), cl.begin(), cl.end());
		}
		return list;
	}
}
