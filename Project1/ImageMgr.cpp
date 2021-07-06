#include "ImageMgr.h"
#include "Image.h"



HRESULT ImageMgr::Init()
{
	return S_OK;
}

void ImageMgr::Release()
{
	DeleteAll();
}

Image* ImageMgr::AddImage(string strKey, int width, int height)
{
	Image* image = FindImage(strKey);
	if (image) return image;

	image = new Image();
	if (FAILED(image->Init(width, height)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));

	return image;
}

Image* ImageMgr::AddImage(string strKey, const char * fileName, int width, int height, bool trans, COLORREF transColor)
{
	Image* image = FindImage(strKey);
	if (image)	return image;

	image = new Image();
	if (FAILED(image->Init(fileName, width, height, trans, transColor)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));

	return image;
}

Image* ImageMgr::AddImage(string strKey, const char * fileName, float x, float y, int width, int height, int keyFrameX, int keyFrameY, bool trans, COLORREF transColor)
{
	Image* image = FindImage(strKey);
	if (image)	return image;

	image = new Image();
	if (FAILED(image->Init(fileName, x, y, width, height, keyFrameX, keyFrameY, trans, transColor)))
	{
		image->Release();
		SAFE_DELETE(image);

		return nullptr;
	}

	mapImageDatas.insert(make_pair(strKey, image));

	return image;
}

Image * ImageMgr::FindImage(string strKey)
{
	map<string, Image*>::iterator iter = mapImageDatas.find(strKey);
	if (iter != mapImageDatas.end())
	{
		return iter->second;
	}

	return nullptr;
}

void ImageMgr::DeleteImage(string strKey)
{
	map<string, Image*>::iterator iter = mapImageDatas.find(strKey);
	if (iter != mapImageDatas.end())
	{
		(iter->second)->Release();
		SAFE_DELETE((iter->second));

		mapImageDatas.erase(iter);	// ���� ������ �ִ� �������� �ش� ���ͷ����͸� ���� ���� ��� 10�������� 9���� ��
	}
}

void ImageMgr::DeleteAll()
{
	map<string, Image*>::iterator iter;
	for (iter = mapImageDatas.begin(); iter != mapImageDatas.end(); /*iter++*/)
	{
		if (iter->second != nullptr)
		{
			// second(value)�� �޸� ����

			(iter->second)->Release();
			SAFE_DELETE((iter->second));

			// key, value (pair) �� �޸� ����
			iter = mapImageDatas.erase(iter);
			// ���� �����ϴ� ����� ���� ��Ҹ� �ڵ����� ��ȯ
		}
		else
		{
			iter++;
		}
	}

	// ���� �޸� ����
	mapImageDatas.clear();
}


ImageMgr::ImageMgr()
{
}


ImageMgr::~ImageMgr()
{
}