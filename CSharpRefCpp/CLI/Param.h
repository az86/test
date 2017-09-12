#pragma once
using namespace System;
namespace CLI
{
	struct CParam
	{
		void *m_pData;
	};

	struct CAlgBase
	{
		virtual void Run(CParam *p) = 0;
	};

	struct CAlg2D : CAlgBase
	{
		virtual void Run (CParam *p){};
	};

	struct CAlg3D : CAlgBase
	{
		virtual void Run (CParam *p){};
	};

	public ref class CAlgMgr
	{
	public:
		CAlgMgr(): m_pAlg(nullptr)
		{
			 m_param = new CParam;
		}
		property IntPtr^ Data2D
		{
			IntPtr^ get ()
			{
				return IntPtr(m_param->m_pData);
			}
			void set(IntPtr^ value)
			{
				m_param->m_pData = value->ToPointer();
				delete m_pAlg;
				m_pAlg = new CAlg2D;
				
			}
		}

		property IntPtr ^Data3D
		{
			IntPtr ^get ()
			{
				return IntPtr(m_param->m_pData);
			}

			void set(IntPtr ^value)
			{
				m_param->m_pData =  (void*)value->ToPointer();
				delete m_pAlg;
				m_pAlg = new CAlg3D;
			}
		}

		void RunAlg()
		{
			m_pAlg->Run(m_param);
		}
	private:
		CParam *m_param;
		CAlgBase *m_pAlg;
	};
}