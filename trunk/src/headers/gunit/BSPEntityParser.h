#ifndef BSP_ENTITY_PARSER_H
#define BSP_ENTITY_PARSER_H

#include<list>
#include<vector>
#include<string>
#include"math/Vector4.h"


namespace siege{
	namespace gunit{

		class BSPEntityParser{
			private:
				std::list<std::string> data;
			public:
				BSPEntityParser();
				BSPEntityParser(char const*);
				void parse(char const*);
				std::list<std::string> getEntities(std::string, std::string) const;
				std::string getValue(std::string, std::string) const;
				std::vector<math::Vector4> getAllSpawnPoints() const;
		}; //BSPEntityParser

	}; //gunit
}; //siege

#endif //BSP_ENTITY_PARSER_H
