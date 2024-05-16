#include <Common/FileSystem.h>
#include <Common/Logger.h>
#include <Common/JSON.h>

#include <matplot/matplot.h>

#include <KMeansClustering.h>

int main(int, char** argv) {
	lstd::initLoggingSystem();
	lstd::initFileSystem(argv);

	KMeansClustering kMeansClustering;

	kMeansClustering.visualizeData();
}