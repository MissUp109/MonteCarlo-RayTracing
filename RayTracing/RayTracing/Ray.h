//
//  Ray.h
//  MonteCarloRayTracing
//
//  Created by leah on 2018/3/28.
//  Copyright © 2018年 Leah Love Cage. All rights reserved.
//

#ifndef Ray_h
#define Ray_h
#include "Double3.h"

struct Ray {
	Double3 original;
	Double3 direction;

	Ray(Double3 ori, Double3 dir) : original(ori), direction(dir) {}
};

#endif /* Ray_h */
