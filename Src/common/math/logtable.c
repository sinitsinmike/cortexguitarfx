#include "stdint.h"

__attribute__ ((section (".qspi_data_fast")))
const float logtable[]= {

-120.000000000f, -119.451132813f, -118.902265625f, -118.353398438f, -117.804531250f, -117.255664063f, -116.706796875f, -116.157929688f, -115.609062500f, -115.060195313f, -114.511328125f, -113.962460938f, -113.413593750f, -112.864726563f, -112.315859375f, -111.766992188f, 
-111.218125000f, -110.669257813f, -110.120390625f, -109.571523438f, -109.022656250f, -108.473789063f, -107.924921875f, -107.376054688f, -106.827187500f, -106.278320313f, -105.729453125f, -105.180585938f, -104.631718750f, -104.082851563f, -103.533984375f, -102.985117188f, 
-102.436250000f, -101.887382813f, -101.338515625f, -100.789648438f, -100.240781250f, -99.691914063f, -99.143046875f, -98.594179688f, -98.045312500f, -97.496445313f, -96.947578125f, -96.398710938f, -95.849843750f, -95.300976563f, -94.752109375f, -94.203242188f, 
-93.654375000f, -93.105507813f, -92.556640625f, -92.007773438f, -91.458906250f, -90.910039063f, -90.361171875f, -89.812304688f, -89.263437500f, -88.714570313f, -88.165703125f, -87.616835938f, -87.067968750f, -86.519101563f, -85.970234375f, -85.421367188f, 
-84.872500000f, -84.323632813f, -83.774765625f, -83.225898438f, -82.677031250f, -82.128164063f, -81.579296875f, -81.030429688f, -80.481562500f, -79.932695313f, -79.383828125f, -78.834960938f, -78.286093750f, -77.737226563f, -77.188359375f, -76.639492188f, 
-76.090625000f, -75.541757813f, -74.992890625f, -74.444023438f, -73.895156250f, -73.346289063f, -72.797421875f, -72.248554688f, -71.699687500f, -71.150820313f, -70.601953125f, -70.053085938f, -69.504218750f, -68.955351563f, -68.406484375f, -67.857617188f, 
-67.308750000f, -66.759882813f, -66.211015625f, -65.662148438f, -65.113281250f, -64.564414063f, -64.015546875f, -63.466679688f, -62.917812500f, -62.368945313f, -61.820078125f, -61.271210938f, -60.722343750f, -60.173476563f, -59.624609375f, -59.075742188f, 
-58.526875000f, -57.978007813f, -57.429140625f, -56.880273438f, -56.331406250f, -55.782539063f, -55.233671875f, -54.684804688f, -54.135937500f, -53.587070313f, -53.038203125f, -52.489335938f, -51.940468750f, -51.391601563f, -50.842734375f, -50.293867188f, 
-49.745000000f, -49.196132813f, -48.647265625f, -48.098398438f, -47.549531250f, -47.000664063f, -46.451796875f, -45.902929688f, -45.354062500f, -44.805195313f, -44.256328125f, -43.707460938f, -43.158593750f, -42.609726563f, -42.060859375f, -41.511992188f, 
-40.963125000f, -40.414257813f, -39.865390625f, -39.316523438f, -38.767656250f, -38.218789063f, -37.669921875f, -37.121054688f, -36.572187500f, -36.023320313f, -35.474453125f, -34.925585938f, -34.376718750f, -33.827851563f, -33.278984375f, -32.730117188f, 
-32.181250000f, -31.632382813f, -31.083515625f, -30.534648438f, -29.985781250f, -29.436914063f, -28.888046875f, -28.339179688f, -27.790312500f, -27.241445313f, -26.692578125f, -26.143710938f, -25.594843750f, -25.045976563f, -24.497109375f, -23.948242188f, 
-23.399375000f, -22.850507813f, -22.301640625f, -21.752773438f, -21.203906250f, -20.655039063f, -20.106171875f, -19.557304688f, -19.008437500f, -18.459570313f, -17.910703125f, -17.361835938f, -16.812968750f, -16.264101563f, -15.715234375f, -15.166367188f, 
-14.617500000f, -14.068632813f, -13.519765625f, -12.970898438f, -12.422031250f, -11.873164063f, -11.324296875f, -10.775429688f, -10.226562500f, -9.677695313f, -9.128828125f, -8.579960938f, -8.031093750f, -7.482226563f, -6.933359375f, -6.384492188f, 
-5.835625000f, -5.286757813f, -4.737890625f, -4.189023438f, -3.640156250f, -3.091289063f, -2.542421875f, -1.993554688f, -1.444687500f, -0.895820313f, -0.346953125f, 0.201914062f, 0.750781250f, 1.299648437f, 1.848515625f, 2.397382812f, 
2.946250000f, 3.495117187f, 4.043984375f, 4.592851562f, 5.141718750f, 5.690585937f, 6.239453125f, 6.788320312f, 7.337187500f, 7.886054687f, 8.434921875f, 8.983789062f, 9.532656250f, 10.081523437f, 10.630390625f, 11.179257812f, 
11.728125000f, 12.276992187f, 12.825859375f, 13.374726562f, 13.923593750f, 14.472460937f, 15.021328125f, 15.570195312f, 16.119062500f, 16.667929687f, 17.216796875f, 17.765664062f, 18.314531250f, 18.863398437f, 19.412265625f, 19.961132812f, 

};

__attribute__ ((section (".qspi_data_fast")))
const float linvalues[] = {
0.000001000f, 0.000001065f, 0.000001135f, 0.000001209f, 0.000001288f, 0.000001372f, 0.000001461f, 0.000001556f, 0.000001658f, 0.000001766f, 0.000001881f, 0.000002004f, 0.000002135f, 0.000002274f, 0.000002422f, 0.000002580f, 
0.000002748f, 0.000002928f, 0.000003119f, 0.000003322f, 0.000003539f, 0.000003770f, 0.000004016f, 0.000004278f, 0.000004557f, 0.000004854f, 0.000005170f, 0.000005508f, 0.000005867f, 0.000006250f, 0.000006657f, 0.000007092f, 
0.000007554f, 0.000008047f, 0.000008572f, 0.000009131f, 0.000009727f, 0.000010361f, 0.000011037f, 0.000011757f, 0.000012524f, 0.000013341f, 0.000014211f, 0.000015138f, 0.000016125f, 0.000017177f, 0.000018298f, 0.000019491f, 
0.000020763f, 0.000022117f, 0.000023560f, 0.000025096f, 0.000026733f, 0.000028477f, 0.000030335f, 0.000032314f, 0.000034421f, 0.000036667f, 0.000039058f, 0.000041606f, 0.000044320f, 0.000047211f, 0.000050291f, 0.000053571f, 
0.000057066f, 0.000060788f, 0.000064753f, 0.000068977f, 0.000073476f, 0.000078269f, 0.000083375f, 0.000088813f, 0.000094607f, 0.000100778f, 0.000107352f, 0.000114354f, 0.000121813f, 0.000129759f, 0.000138224f, 0.000147240f, 
0.000156844f, 0.000167075f, 0.000177974f, 0.000189583f, 0.000201949f, 0.000215122f, 0.000229155f, 0.000244103f, 0.000260025f, 0.000276987f, 0.000295055f, 0.000314301f, 0.000334803f, 0.000356642f, 0.000379906f, 0.000404687f, 
0.000431085f, 0.000459204f, 0.000489158f, 0.000521066f, 0.000555055f, 0.000591261f, 0.000629829f, 0.000670913f, 0.000714676f, 0.000761295f, 0.000810954f, 0.000863852f, 0.000920201f, 0.000980226f, 0.001044166f, 0.001112277f, 
0.001184831f, 0.001262117f, 0.001344445f, 0.001432143f, 0.001525561f, 0.001625074f, 0.001731077f, 0.001843995f, 0.001964279f, 0.002092409f, 0.002228896f, 0.002374287f, 0.002529162f, 0.002694139f, 0.002869877f, 0.003057079f, 
0.003256492f, 0.003468913f, 0.003695190f, 0.003936226f, 0.004192986f, 0.004466494f, 0.004757844f, 0.005068197f, 0.005398795f, 0.005750959f, 0.006126093f, 0.006525698f, 0.006951369f, 0.007404806f, 0.007887821f, 0.008402343f, 
0.008950427f, 0.009534263f, 0.010156182f, 0.010818669f, 0.011524370f, 0.012276104f, 0.013076873f, 0.013929876f, 0.014838521f, 0.015806437f, 0.016837490f, 0.017935798f, 0.019105749f, 0.020352015f, 0.021679576f, 0.023093733f, 
0.024600136f, 0.026204801f, 0.027914138f, 0.029734975f, 0.031674585f, 0.033740716f, 0.035941621f, 0.038286090f, 0.040783489f, 0.043443793f, 0.046277628f, 0.049296315f, 0.052511910f, 0.055937258f, 0.059586041f, 0.063472834f, 
0.067613163f, 0.072023564f, 0.076721656f, 0.081726204f, 0.087057199f, 0.092735933f, 0.098785091f, 0.105228836f, 0.112092905f, 0.119404717f, 0.127193478f, 0.135490300f, 0.144328322f, 0.153742848f, 0.163771483f, 0.174454285f, 
0.185833925f, 0.197955859f, 0.210868505f, 0.224623442f, 0.239275613f, 0.254883544f, 0.271509579f, 0.289220129f, 0.308085937f, 0.328182360f, 0.349589672f, 0.372393381f, 0.396684574f, 0.422560280f, 0.450123857f, 0.479485403f, 
0.510762201f, 0.544079183f, 0.579569428f, 0.617374700f, 0.657646007f, 0.700544208f, 0.746240656f, 0.794917880f, 0.846770316f, 0.902005082f, 0.960842808f, 1.023518515f, 1.090282553f, 1.161401605f, 1.237159747f, 1.317859588f, 
1.403823473f, 1.495394777f, 1.592939270f, 1.696846583f, 1.807531762f, 1.925436928f, 2.051033039f, 2.184821775f, 2.327337541f, 2.479149600f, 2.640864349f, 2.813127739f, 2.996627857f, 3.192097675f, 3.400317975f, 3.622120470f, 
3.858391125f, 4.110073699f, 4.378173508f, 4.663761448f, 4.967978269f, 5.292039131f, 5.637238460f, 6.004955116f, 6.396657903f, 6.813911434f, 7.258382382f, 7.731846139f, 8.236193902f, 8.773440232f, 9.345731103f, 9.955352465f, 

};

__attribute__ ((section (".qspi_code")))
float fastlog(float x)
{
    uint32_t c=0;
    if (x < linvalues[0])
    {
        return logtable[0];
    }
    if (x > linvalues[255])
    {
        return logtable[255];
    }
    while(linvalues[c] < x)
    {
        c++;
    }
    return logtable[c-1] + (logtable[c] - logtable[c-1])/(linvalues[c] - linvalues[c-1])*(x-linvalues[c-1]);
}

