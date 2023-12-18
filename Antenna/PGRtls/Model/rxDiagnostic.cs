using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.ComponentModel;
using System.Threading;

namespace PGRtls.Model
{
    class rxDiagnostic:INotifyPropertyChanged
    {
        private SynchronizationContext syncContext;
        //计算常量
        public double A = 121.74;

        public double zeta = 0.35;

        private double Little_Filter(double now_data, double last_data)
        {
            return (ushort)(zeta * now_data + (1 - zeta) * last_data);
        }

        //最大噪声
        private double _maxNoise;
        private double last_maxNoise;
        private bool is_mN_init = false;
        public double maxNoise
        {
            get
            {
                return _maxNoise;
            }
            set
            {
                if (!is_mN_init)
                {
                    _maxNoise = value;
                    is_mN_init = true;
                }                   
                else
                {
                    last_maxNoise = _maxNoise;
                    _maxNoise = Little_Filter(value, last_maxNoise);
                }                
                OnPropertyChanged("maxNoise");
            }
        }
        
        //噪声均方根值
        private double _stdNoise;
        private double last_stdNoise;
        private bool is_std_init = false;
        public double stdNoise
        {
            get
            {
                return _stdNoise;
            }
            set
            {
                if (!is_std_init)
                {
                    _stdNoise = value;
                    is_std_init = true;
                }
                else
                {
                    last_stdNoise = _stdNoise;
                    _stdNoise = Little_Filter(value, last_stdNoise);
                }
                OnPropertyChanged("stdNoise");
            }
        }

        //第一路径分量1
        private double _firstPathAmp1;
        private double last_firstPathAmp1;
        private bool is_FP1_init = false;
        public double firstPathAmp1
        {
            get
            {
                return _firstPathAmp1;
            }
            set
            {
                if (!is_FP1_init)
                {
                    _firstPathAmp1 = value;
                    is_FP1_init = true;
                }
                else
                {
                    last_firstPathAmp1 = _firstPathAmp1;
                    _firstPathAmp1 = Little_Filter(value, last_firstPathAmp1);
                }
                OnPropertyChanged("firstPathAmp1");
            }
        }

        //第一路径分量2
        private double _firstPathAmp2;
        private double last_firstPathAmp2;
        private bool is_FP2_init = false;
        public double firstPathAmp2
        {
            get
            {
                return _firstPathAmp2;
            }
            set
            {
                if (!is_FP2_init)
                {
                    _firstPathAmp2 = value;
                    is_FP1_init = true;
                }
                else
                {
                    last_firstPathAmp2 = _firstPathAmp2;
                    _firstPathAmp2 = Little_Filter(value, last_firstPathAmp2);
                }
                OnPropertyChanged("firstPathAmp2");
            }
        }

        //第一路径分量3
        private double _firstPathAmp3;
        private double last_firstPathAmp3;
        private bool is_FP3_init = false;
        public double firstPathAmp3
        {
            get
            {
                return _firstPathAmp3;
            }
            set
            {
                if (!is_FP3_init)
                {
                    _firstPathAmp3 = value;
                    is_FP1_init = true;
                }
                else
                {
                    last_firstPathAmp3 = _firstPathAmp3;
                    _firstPathAmp3 = Little_Filter(value, last_firstPathAmp3);
                }
                OnPropertyChanged("firstPathAmp3");
            }
        }

        //最大CIR值
        private double _maxGrowthCIR;
        private double last_maxGrowthCIR;
        private bool is_CIR_init = false;
        public double maxGrowthCIR
        {
            get
            {
                return _maxGrowthCIR;
            }
            set
            {
                if (!is_CIR_init)
                {
                    _maxGrowthCIR = value;
                    is_CIR_init = true;
                }
                else
                {
                    last_maxGrowthCIR = _maxGrowthCIR;
                    _maxGrowthCIR = Little_Filter(value, last_maxGrowthCIR);
                }
                OnPropertyChanged("maxGrowthCIR");
            }
        }

        //接收前导码数量
        private double _rxPreamCount;
        private double last_rxPreamCount;
        private bool is_Pream_init = false;
        public double rxPreamCount
        {
            get
            {
                return _rxPreamCount;
            }
            set
            {
                if (!is_Pream_init)
                {
                    _rxPreamCount = value;
                    is_Pream_init = true;
                }
                else
                {
                    last_rxPreamCount = _rxPreamCount;
                    _rxPreamCount = Little_Filter(value, last_rxPreamCount);
                }               
                OnPropertyChanged("rxPreamCount");
            }
        }

        //第一路径值
        private double _firstPath;
        private double last_firstPath;
        private bool is_FP_init = false;
        public double firstPath
        {
            get
            {
                return _firstPath;
            }
            set
            {
                if(!is_FP_init)
                {
                    _firstPath = value;
                    is_FP_init = true;
                }
                else
                {
                    last_firstPath = _firstPath;
                    _firstPath = Little_Filter(value, last_firstPath);                 
                }
                OnPropertyChanged("firstPath");
            }
        }

        //根据第一路径计算的接收强度
        private string _FPPower;
        public string FPPower
        {
            get
            {
                return _FPPower;
            }
            set
            {
                _FPPower = value;
                OnPropertyChanged("FPPower");
            }
        }

        //根据接收强度估计理论接收强度
        private string _RxPower;
        public string RxPower
        {
            get
            {
                return _RxPower;
            }
            set
            {
                _RxPower = value;
                OnPropertyChanged("RxPower");
            }
        }

        public rxDiagnostic()
        {
            syncContext = SynchronizationContext.Current;
        }

        public void rx_diagnostic_init()
        {
            is_CIR_init = false;
            is_FP1_init = false;
            is_FP2_init = false;
            is_FP3_init = false;
            is_FP_init = false;
            is_mN_init = false;
            is_Pream_init = false;
            is_std_init = false;
        }

        protected internal virtual void OnPropertyChanged(string propertyName)
        {
            var handler = PropertyChanged;
            if (handler != null)
            {
                if (syncContext != null)
                    syncContext.Post(_ => handler(this, new PropertyChangedEventArgs(propertyName)), null);
                else
                    handler(this, new PropertyChangedEventArgs(propertyName));
            }
        }
        public event PropertyChangedEventHandler PropertyChanged;
    }
}
