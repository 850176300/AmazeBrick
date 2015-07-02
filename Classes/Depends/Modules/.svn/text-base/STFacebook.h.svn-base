#ifndef _STFACEBOOK_H_
#define _STFACEBOOK_H_
#include <string>
#include <map>
using namespace std;
class STFacebook {
    static STFacebook *_instance;
public:
	static STFacebook* getInstance();
	static void purgeInstance();

	virtual ~STFacebook();

public:
	// the below four methods used to inform game change status
	// and implements other game logic, and the source file
	// is placed in "Classes" directory
	void onPostStatus(int tag, bool bSuccess);
	void onPostPhoto(int tag, bool bSuccess);
	void onPostRichContent(int tag, bool bSuccess);
	void onPostTimeOut(int tag);

public:
	// in Android OS, the below methods need communicate with jni,
	// so the relative source file is placed in jni directory under
	// the proj.androd
	void NativePostStatusUpdate(int tag, std::string text);
	void NativePostPhotoFromAsset(int tag, std::string filename, std::string message = "");
	// FIXME: maybe this method will not be called(do not know drawable id)
	void NativePostPhotoFromDrawable(int tag, int drawableId, std::string message = "");
	void NativePostPhotoFromFile(int tag, std::string filename, std::string message = "");

	void NativePostRichContentAsset(int tag, std::string message, std::string link, std::string assetFileName);
	// FIXME: maybe this method will not be called(do not know drawable id)
	void NativePostRichContentDrawable(int tag, std::string message, std::string link, int imgId);
	void NativePostRichContentFile(int tag, std::string message, std::string link, std::string fileName);
    
    void NativePostStory(map<string ,string > pStory);

private:
	STFacebook();
};

#endif