#include "SoundManager.h"

HRESULT SoundManager::Init()
{
	// ���� �ý��� ����
	System_Create(&system);

	// ä�� ����
	system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, NULL);  // ä�μ�, �÷��� ,����̹��� �����͸� �޾ƿü� ����

	// ���� , ä�� �����Ҵ�
	sound = new Sound*[TOTALSOUNDBUFFER];
	channel = new Channel*[TOTALSOUNDBUFFER];

	memset(sound, 0, sizeof(Sound*) * TOTALSOUNDBUFFER);
	memset(channel, 0, sizeof(Channel*) * TOTALSOUNDBUFFER);


	return S_OK;
}

void SoundManager::Release()
{
	SAFE_ARR_DELETE(sound);
	SAFE_ARR_DELETE(channel);

	system->close();
	system->release();

}

void SoundManager::Update()
{
	if (system)
	{
		system->update();
	}
}

void SoundManager::AddSound(string key, string filePath, bool isBGM, bool isLoop)
{
	if (isLoop)
	{
		if (isBGM)
		{
			system->createStream(filePath.c_str(), FMOD_LOOP_NORMAL,
				0, &sound[mapSoundDatas.size()]);	// bgm �϶�

		}
		else
		{
			system->createSound(filePath.c_str(), FMOD_LOOP_NORMAL,
				0, &sound[mapSoundDatas.size()]);	// bgm�� �ƴ����� �����Ǵ� ����
		}
	}
	else
	{
		system->createSound(filePath.c_str(), FMOD_DEFAULT,
			0, &sound[mapSoundDatas.size()]); // ����Ʈ �ݺ����� �ʴ�, �������� �ʴ� ����
	}

	mapSoundDatas.insert(make_pair(key, &sound[mapSoundDatas.size()]));
}

void SoundManager::Play(string key, float volume)
{
	map<string, Sound**>::iterator it;
	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			system->playSound(FMOD_CHANNEL_REUSE, (*mapSoundDatas[key]), false, &channel[count]);

			channel[count]->setVolume(volume);

			break;
		}
	}

}

void SoundManager::Stop(string key)
{
	map<string, Sound**>::iterator it;
	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->stop();
			break;
		}
	}
}

void SoundManager::Pause(string key)
{
	map<string, Sound**>::iterator it;
	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::Resume(string key)
{
	map<string, Sound**>::iterator it;
	int count = 0;

	for (it = mapSoundDatas.begin(); it != mapSoundDatas.end(); it++, count++)
	{
		if (it->first == key)
		{
			channel[count]->setPaused(false);
			break;
		}
	}
}

SoundManager::SoundManager()
	: system(nullptr)
	, sound(nullptr)
	, channel(nullptr)
{
}

SoundManager::~SoundManager()
{
}
