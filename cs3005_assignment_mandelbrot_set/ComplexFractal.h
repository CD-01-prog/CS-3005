#ifndef _COMPLEXFRACTAL_H_
#define _COMPLEXFRACTAL_H_
#include <iostream>
#include "NumberGrid.h"

class ComplexFractal:public NumberGrid {
	private:
		std::vector<int> mSet;
		int mheight;
		int mwidth;
		double mdelta_x;
		double mdelta_y;
		double mmin_x;
		double mmax_x;
		double mmin_y;
		double mmax_y;
	public:
		ComplexFractal();

		ComplexFractal( const int& height, const int& width, const double& min_x, const double& max_x, const double& min_y, const double& max_y);

		virtual ~ComplexFractal();

		double getMinX( ) const;

		double getMaxX( ) const;

		double getMinY( ) const;

		double getMaxY( ) const;

		virtual void setGridSize( const int& height, const int& width );

		void setPlaneSize( const double& min_x, const double& max_x, const double& min_y, const double& max_y );

		double getDeltaX( ) const;

		double getDeltaY( ) const;

		void setDeltas( const double& delta_x, const double& delta_y );

		double calculateDeltaX( ) const;

		double calculateDeltaY( ) const;

		double calculatePlaneYFromPixelRow( const int& row ) const;

		double calculatePlaneXFromPixelColumn( const int& column ) const;

		void calculatePlaneCoordinatesFromPixelCoordinates( const int& row, const int& column, double& x, double& y ) const;

};
#endif
