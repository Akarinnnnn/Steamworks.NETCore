#include "pch.h"
#include <steam_api.h>
#include <string>
//using namespace msclr::interop;
using mstring = System::String;
using std::string;
using mbuff = cli::array<unsigned char>;
using System::Text::Encoding;
using not_impl = System::NotImplementedException;


#define NATIVEPTR_CHECK 	\
auto* native = ::SteamRemoteStorage();\
if(!native) throw gcnew System::InvalidOperationException("SteamRemoteStorage can not be get.")

namespace Steamworks::NETCore 
{
	extern std::string mstr2u8(mstring^ str);

	/// <summary>
	/// SteamRemoteStorage Class, call Init before using any other methods.
	/// </summary>
	public ref class SteamRemoteStorage
	{
	public:

		/// <summary>
		/// file operation
		/// </summary>
		bool	FileWrite(mstring^ fileName, mbuff^ data, int bytesToWrite)
		{
			NATIVEPTR_CHECK;

			pin_ptr<unsigned char> buffbeg = &data[0];
			return native->FileWrite(mstr2u8(fileName).c_str(), buffbeg, bytesToWrite);
		}
		
		/// <summary>
		/// Read a file
		/// </summary>
		/// <param name="fileName"></param>
		/// <param name="data"></param>
		/// <created>Fa¸ë,2020/2/25</created>
		/// <changed>Fa¸ë,2020/2/25</changed>
		int32 FileRead(mstring^ fileName, mbuff^ data, int bytesToRead)
		{
			NATIVEPTR_CHECK;

			pin_ptr<unsigned char> buffbeg = &data[0];
			return native->FileWrite(mstr2u8(fileName).c_str(), buffbeg, bytesToRead);
		}

		/// <summary>
		/// file operation
		/// </summary>
		SteamAPICall_t FileWriteAsync(mstring^ fileName, mbuff^ data, uint32 bytesToWrite) { throw gcnew not_impl(); }
		SteamAPICall_t FileReadAsync(const char* pchFile, uint32 nOffset, uint32 cubToRead) { throw gcnew not_impl(); }
		bool	FileReadAsyncComplete(SteamAPICall_t hReadCall, void* pvBuffer, uint32 cubToRead) { throw gcnew not_impl(); }
		bool	FileForget(const char* pchFile) { throw gcnew not_impl(); }
		bool	FileDelete(const char* pchFile) { throw gcnew not_impl(); }
		SteamAPICall_t FileShare(const char* pchFile) { throw gcnew not_impl(); }
		bool	SetSyncPlatforms(const char* pchFile, ERemoteStoragePlatform eRemoteStoragePlatform) { throw gcnew not_impl(); }

		// file operations that cause network IO
		UGCFileWriteStreamHandle_t FileWriteStreamOpen(const char* pchFile) { throw gcnew not_impl(); }
		bool FileWriteStreamWriteChunk(UGCFileWriteStreamHandle_t writeHandle, const void* pvData, int32 cubData) { throw gcnew not_impl(); }
		bool FileWriteStreamClose(UGCFileWriteStreamHandle_t writeHandle) { throw gcnew not_impl(); }
		bool FileWriteStreamCancel(UGCFileWriteStreamHandle_t writeHandle) { throw gcnew not_impl(); }

		// file information
		bool	FileExists(const char* pchFile) { throw gcnew not_impl(); }
		bool	FilePersisted(const char* pchFile) { throw gcnew not_impl(); }
		int32	GetFileSize(const char* pchFile) { throw gcnew not_impl(); }
		int64	GetFileTimestamp(const char* pchFile) { throw gcnew not_impl(); }
		ERemoteStoragePlatform GetSyncPlatforms(const char* pchFile) { throw gcnew not_impl(); }

		// iteration
		int32 GetFileCount() { throw gcnew not_impl(); }
		const char* GetFileNameAndSize(int iFile, int32* pnFileSizeInBytes) { throw gcnew not_impl(); }

		// configuration management
		bool GetQuota(uint64* pnTotalBytes, uint64* puAvailableBytes) { throw gcnew not_impl(); }
		bool IsCloudEnabledForAccount() { throw gcnew not_impl(); }
		bool IsCloudEnabledForApp() { throw gcnew not_impl(); }
		void SetCloudEnabledForApp(bool bEnabled) { throw gcnew not_impl(); }

		// user generated content

		// Downloads a UGC file.  A priority value of 0 will download the file immediately,
		// otherwise it will wait to download the file until all downloads with a lower priority
		// value are completed.  Downloads with equal priority will occur simultaneously.
		SteamAPICall_t UGCDownload(UGCHandle_t hContent, uint32 unPriority) { throw gcnew not_impl(); }

		// Gets the amount of data downloaded so far for a piece of content. pnBytesExpected can be 0 if function returns false
		// or if the transfer hasn't started yet, so be careful to check for that before dividing to get a percentage
		bool	GetUGCDownloadProgress(UGCHandle_t hContent, int32* pnBytesDownloaded, int32* pnBytesExpected) { throw gcnew not_impl(); }

		// Gets metadata for a file after it has been downloaded. This is the same metadata given in the RemoteStorageDownloadUGCResult_t call result
		bool	GetUGCDetails(UGCHandle_t hContent, AppId_t% pnAppID, mstring^% name,
			int32% pnFileSizeInBytes, OUT_STRUCT() CSteamID* pSteamIDOwner)
		{ throw gcnew not_impl(); }

		// After download, gets the content of the file.  
		// Small files can be read all at once by calling this function with an offset of 0 and cubDataToRead equal to the size of the file.
		// Larger files can be read in chunks to reduce memory usage (since both sides of the IPC client and the game itself must allocate
		// enough memory for each chunk).  Once the last byte is read, the file is implicitly closed and further calls to UGCRead will fail
		// unless UGCDownload is called again.
		// For especially large files (anything over 100MB) it is a requirement that the file is read in chunks.
		int32	UGCRead(UGCHandle_t hContent, void* pvData, int32 cubDataToRead, uint32 cOffset, EUGCReadAction eAction) { throw gcnew not_impl(); }

		// Functions to iterate through UGC that has finished downloading but has not yet been read via UGCRead()
		int32	GetCachedUGCCount() { throw gcnew not_impl(); }
		virtual	UGCHandle_t GetCachedUGCHandle(int32 iCachedContent) { throw gcnew not_impl(); }

		// The following functions are only necessary on the Playstation 3. On PC & Mac, the Steam client will handle these operations for you
		// On Playstation 3, the game controls which files are stored in the cloud, via FilePersist, FileFetch, and FileForget.
		// publishing UGC
		SteamAPICall_t	PublishWorkshopFile(const char* pchFile, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags, EWorkshopFileType eWorkshopFileType) { throw gcnew not_impl(); }
		PublishedFileUpdateHandle_t CreatePublishedFileUpdateRequest(PublishedFileId_t unPublishedFileId) { throw gcnew not_impl(); }
		bool UpdatePublishedFileFile(PublishedFileUpdateHandle_t updateHandle, const char* pchFile) { throw gcnew not_impl(); }
		bool UpdatePublishedFilePreviewFile(PublishedFileUpdateHandle_t updateHandle, const char* pchPreviewFile) { throw gcnew not_impl(); }
		bool UpdatePublishedFileTitle(PublishedFileUpdateHandle_t updateHandle, const char* pchTitle) { throw gcnew not_impl(); }
		bool UpdatePublishedFileDescription(PublishedFileUpdateHandle_t updateHandle, const char* pchDescription) { throw gcnew not_impl(); }
		bool UpdatePublishedFileVisibility(PublishedFileUpdateHandle_t updateHandle, ERemoteStoragePublishedFileVisibility eVisibility) { throw gcnew not_impl(); }
		bool UpdatePublishedFileTags(PublishedFileUpdateHandle_t updateHandle, SteamParamStringArray_t* pTags) { throw gcnew not_impl(); }
		SteamAPICall_t	CommitPublishedFileUpdate(PublishedFileUpdateHandle_t updateHandle) { throw gcnew not_impl(); }
		// Gets published file details for the given publishedfileid.  If unMaxSecondsOld is greater than 0,
		// cached data may be returned, depending on how long ago it was cached.  A value of 0 will force a refresh.
		// A value of k_WorkshopForceLoadPublishedFileDetailsFromCache will use cached data if it exists, no matter how old it is.
		SteamAPICall_t	GetPublishedFileDetails(PublishedFileId_t unPublishedFileId, uint32 unMaxSecondsOld) { throw gcnew not_impl(); }
		SteamAPICall_t	DeletePublishedFile(PublishedFileId_t unPublishedFileId) { throw gcnew not_impl(); }
		// enumerate the files that the current user published with this app
		SteamAPICall_t	EnumerateUserPublishedFiles(uint32 unStartIndex) { throw gcnew not_impl(); }
		SteamAPICall_t	SubscribePublishedFile(PublishedFileId_t unPublishedFileId) { throw gcnew not_impl(); }
		SteamAPICall_t	EnumerateUserSubscribedFiles(uint32 unStartIndex) { throw gcnew not_impl(); }
		SteamAPICall_t	UnsubscribePublishedFile(PublishedFileId_t unPublishedFileId) { throw gcnew not_impl(); }
		bool UpdatePublishedFileSetChangeDescription(PublishedFileUpdateHandle_t updateHandle, const char* pchChangeDescription) { throw gcnew not_impl(); }
		SteamAPICall_t	GetPublishedItemVoteDetails(PublishedFileId_t unPublishedFileId) { throw gcnew not_impl(); }
		SteamAPICall_t	UpdateUserPublishedItemVote(PublishedFileId_t unPublishedFileId, bool bVoteUp) { throw gcnew not_impl(); }
		SteamAPICall_t	GetUserPublishedItemVoteDetails(PublishedFileId_t unPublishedFileId) { throw gcnew not_impl(); }
		SteamAPICall_t	EnumerateUserSharedWorkshopFiles(CSteamID steamId, uint32 unStartIndex, SteamParamStringArray_t* pRequiredTags, SteamParamStringArray_t* pExcludedTags) { throw gcnew not_impl(); }
		SteamAPICall_t	PublishVideo(EWorkshopVideoProvider eVideoProvider, const char* pchVideoAccount, const char* pchVideoIdentifier, const char* pchPreviewFile, AppId_t nConsumerAppId, const char* pchTitle, const char* pchDescription, ERemoteStoragePublishedFileVisibility eVisibility, SteamParamStringArray_t* pTags) { throw gcnew not_impl(); }
		SteamAPICall_t	SetUserPublishedFileAction(PublishedFileId_t unPublishedFileId, EWorkshopFileAction eAction) { throw gcnew not_impl(); }
		SteamAPICall_t	EnumeratePublishedFilesByUserAction(EWorkshopFileAction eAction, uint32 unStartIndex) { throw gcnew not_impl(); }
		// this method enumerates the public view of workshop files
		SteamAPICall_t	EnumeratePublishedWorkshopFiles(EWorkshopEnumerationType eEnumerationType, uint32 unStartIndex, uint32 unCount, uint32 unDays, SteamParamStringArray_t* pTags, SteamParamStringArray_t* pUserTags) { throw gcnew not_impl(); }

		SteamAPICall_t UGCDownloadToLocation(UGCHandle_t hContent, const char* pchLocation, uint32 unPriority) { throw gcnew not_impl(); }
	private:
	};
}