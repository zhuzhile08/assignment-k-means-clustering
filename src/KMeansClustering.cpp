#include <KMeansClustering.h>

#include <matplot/matplot.h>
#include <matplot/util/colors.h>

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>

void KMeansClustering::visualizeData() {
	for (const auto& genera : m_data) {
		matplot::tiledlayout(1, 2);

		lstd::Array<matplot::axes_handle, 2> leaves;
		leaves[0] = matplot::nexttile(); // sepal
		leaves[1] = matplot::nexttile(); // petal

		for (const auto& species : *genera) {
			auto& specimens = species->get<lstd::Json::array_type>();

			lstd::Vector<lstd::Json::floating_type> sepalXCoords;
			lstd::Vector<lstd::Json::floating_type> sepalYCoords;

			lstd::Vector<lstd::Json::floating_type> petalXCoords;
			lstd::Vector<lstd::Json::floating_type> petalYCoords;

			sepalXCoords.reserve(specimens.size());
			sepalYCoords.reserve(specimens.size());

			petalXCoords.reserve(specimens.size());
			petalYCoords.reserve(specimens.size());
			
			for (const auto& specimen : specimens) {
				sepalXCoords.pushBack(specimen->at(0).get<lstd::Json::floating_type>());
				sepalYCoords.pushBack(specimen->at(1).get<lstd::Json::floating_type>());

				petalXCoords.pushBack(specimen->at(2).get<lstd::Json::floating_type>());
				petalYCoords.pushBack(specimen->at(3).get<lstd::Json::floating_type>());
			}

			leaves[0]->plot(
				sepalXCoords, 
				sepalYCoords,
				"o"
			);
			leaves[0]->hold(matplot::on);

			leaves[1]->plot(
				petalXCoords, 
				petalYCoords, 
				"o"
			);
			leaves[1]->hold(matplot::on);
		}

		for (auto& leave : leaves) {
			leave->axis({ 0, 10, 0, 10 });
			leave->xlabel("Length:");
			leave->ylabel("Width:");
		}

		leaves[0]->title("Sepal leaves:");
		leaves[1]->title("Petal leaves:");

		matplot::sgtitle(fmt::format("Species data from genus: {}", genera->name()));

		matplot::show();
	}
}
