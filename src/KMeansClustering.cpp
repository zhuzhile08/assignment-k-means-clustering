#include <KMeansClustering.h>

#include <matplot/matplot.h>

void KMeansClustering::visualizeData() {
    for (const auto& genera : m_data) {
        for (const auto& species : *genera) {
            auto index = (&species - genera->begin());

            matplot::subplot(2, genera->size(), index);
			matplot::title(fmt::format("Species: {}", species->name()));

            
            matplot::subplot(2, genera->size(), index + genera->size());
        }

        matplot::sgtitle(fmt::format("Species data from genus: {}", genera->name()));

        matplot::show();
    }
}
