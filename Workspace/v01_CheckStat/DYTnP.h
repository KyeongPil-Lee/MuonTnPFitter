#include <TString.h>
namespace DYTnP
{

vector<Double_t> vec_ptBinEdge_IDISO = {17, 23, 28, 40, 50, 60, 120, 200, 500, 1000};
vector<Double_t> vec_ptBinEdge_trig = {17, 22, 24, 26, 28, 40, 50, 60, 120, 200, 500, 1000};

// -- 0.1 bin size
// vector<Double_t> vec_etaBinEdge =
// {
//   -2.4, -2.3, -2.2, -2.1, -2.0, 
//   -1.9, -1.8, -1.7, -1.6, -1.5, -1.4, -1.3, -1.2, -1.1, -1.0, 
//   -0.9, -0.8, -0.7, -0.6, -0.5, -0.4, -0.3, -0.2, -0.1, 0,
//   0.1, 0.2, 0.3, 0.4, 0.5, 0.6, 0.7, 0.8, 0.9, 1.0, 
//   1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9, 2.0, 
//   2.1, 2.2, 2.3, 2.4
// };

// -- 0.2 bin size
vector<Double_t> vec_etaBinEdge =
{
  -2.4, -2.2, -2.0, 
  -1.8, -1.6, -1.4, -1.2, -1.0, 
  -0.8, -0.6, -0.4, -0.2, 0,
  0.2, 0.4, 0.6, 0.8, 1.0, 
  1.2, 1.4, 1.6, 1.8, 2.0, 
  2.2, 2.4
};

TString ntuplePath_DataBtoF = "/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016BtoF_GoldenJSON.root";
TString ntuplePath_DataGtoH = "/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_LegacyRereco07Aug17_SingleMuon_Run2016GtoH_GoldenJSON.root";
TString ntuplePath_MC = "/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO.root";
TString ntuplePath_MCWeightedToBtoF = "/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToBtoF.root";
TString ntuplePath_MCWeightedToGtoH = "/scratch/kplee/TagProbe/TnPTree/2016/TnPTreeZ_Summer16_DYLL_M50_aMCNLO_weightedToGtoH.root";

}; // -- end of namespace