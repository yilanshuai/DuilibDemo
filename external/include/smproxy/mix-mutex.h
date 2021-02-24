/*
   mutex.h
   Header for a Pthread mutex class in C++.
   ------------------------------------------
   Copyright © 2013 [Vic Hargrave - http://vichargrave.com]
   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at
       http://www.apache.org/licenses/LICENSE-2.0
   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef __mix_mutex_h__
#define __mix_mutex_h__

#if defined(__linux__)
#include <pthread.h>
#else
#include <Windows.h>
#endif

class MixMutex
{

#if defined(__linux__)
    pthread_mutex_t  m_mutex;
#else
	HANDLE m_mutex;
#endif

  public:
    // just initialize to defaults
    MixMutex(const char mutex_name[]) {

#if defined(__linux__)
		pthread_mutex_init(&m_mutex, mutex_name); 
#else
		m_mutex=CreateMutexA(NULL,FALSE,mutex_name);
#endif
	}
    virtual ~MixMutex() { 
#if defined(__linux__)
		pthread_mutex_destroy(&m_mutex); 
#else
		ReleaseMutex(m_mutex);
		CloseHandle(m_mutex);
#endif
	}

    int lock() { 
#if defined(__linux__)
		return  pthread_mutex_lock(&m_mutex); 
#else
		DWORD dwWaitResult;  
		dwWaitResult = WaitForSingleObject((HANDLE) m_mutex, INFINITE);  
		return dwWaitResult != WAIT_OBJECT_0 ? -1 : NO_ERROR;  
#endif
	}
    int trylock() {
#if defined(__linux__)
		return  pthread_mutex_trylock(&m_mutex); 
#else
		DWORD dwWaitResult;  

		dwWaitResult = WaitForSingleObject((HANDLE) m_mutex, 0);  
		if (dwWaitResult != WAIT_OBJECT_0 && dwWaitResult != WAIT_TIMEOUT)  
		{

		}
		return (dwWaitResult == WAIT_OBJECT_0) ? 0 : -1;  
#endif
	
	}
    int unlock() { 
#if defined(__linux__)
		return  pthread_mutex_unlock(&m_mutex); 
#else
		return ReleaseMutex((HANDLE) m_mutex); 
#endif	
	}   
};

class UseMixMutex
{
	MixMutex * mixMutex;

public:

        UseMixMutex(const char mutex_name[]) {
		mixMutex = new MixMutex(mutex_name);
		mixMutex->lock();
	}
	virtual ~UseMixMutex() { 
		mixMutex->unlock();
		delete(mixMutex);
	}
};

#endif
