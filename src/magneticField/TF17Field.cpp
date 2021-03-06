#include "crpropa/magneticField/TF17Field.h"
#include "crpropa/Units.h"

#include <algorithm>
#include <string>

namespace crpropa {
using namespace std;

TF17Field::TF17Field(TF17DiskModel disk_model_, TF17HaloModel halo_model_) {
    disk_model = disk_model_; 
    halo_model = halo_model_;

    useHaloField = true;
    useDiskField = true;

    if ((halo_model == TF17HaloModel::C0) && (disk_model == TF17DiskModel::Ad1)) {
        // disk parameters
        set_r1_disk(3 * kpc);
        set_B1_disk(19.0 * muG);
        set_H_disk(0.055 * kpc);
        set_phi_star_disk(-54 * M_PI / 180);
        set_a_disk(0.9 / kpc / kpc);
        // halo parameters
        set_z1_halo(0);
        set_B1_halo(0.36 * muG);
        set_L_halo(3.0 * kpc);
        set_a_halo(1.17 / kpc / kpc);
        // shared parameters
        set_p0(-7.9 * M_PI / 180);
        set_Hp(5 * kpc);
        set_Lp(50 * kpc); // > 18 kpc
            
    } else if ((halo_model == TF17HaloModel::C0) && (disk_model == TF17DiskModel::Bd1)) {
        // disk parameters
        set_r1_disk(3 * kpc);
        set_B1_disk(2.0 * muG);
        set_H_disk(0.32 * kpc);
        set_phi_star_disk(153 * M_PI / 180);
        // halo parameters
        set_z1_halo(0);
        set_B1_halo(0.29 * muG);
        set_L_halo(3.4 * kpc);
        set_a_halo(0.88 / kpc / kpc);
        // shared parameters
        set_p0(-7.2 * M_PI / 180);
        set_Hp(9 * kpc);
        set_Lp(50 * kpc); // > 16 kpc

    } else if ((halo_model == TF17HaloModel::C0) && (disk_model == TF17DiskModel::Dd1)) {
        // disk parameters
        set_z1_disk(1.5 * kpc);
        set_B1_disk(0.065 * muG);
        set_L_disk(9.8 * kpc);
        set_phi_star_disk(14 * M_PI / 180);
        // halo parameters
        set_z1_halo(0);
        set_B1_halo(0.18 * muG);
        set_L_halo(4.8 * kpc);
        set_a_halo(0.61 / kpc / kpc);
        // shared parameters
        set_p0(-7.4 * M_PI / 180);
        set_Hp(4.2 * kpc);
        set_Lp(50 * kpc); // > 22 kpc

    } else if ((halo_model == TF17HaloModel::C1) && (disk_model == TF17DiskModel::Ad1)) {
        // disk parameters
        set_r1_disk(3 * kpc);
        set_B1_disk(32.0 * muG);
        set_H_disk(0.054 * kpc);
        set_phi_star_disk(-31 * M_PI / 180);
        set_a_disk(0.031 / kpc / kpc);
        // halo parameters
        set_z1_halo(0);
        set_B1_halo(9.0 * muG);
        set_L_halo(2.1 * kpc);
        set_phi_star_halo(198 * M_PI / 180);
        set_a_halo(0.33 / kpc / kpc);
        // shared parameters
        set_p0(-9.1 * M_PI / 180);
        set_Hp(1.2 * kpc);
        set_Lp(50 * kpc); // > 38 kpc

    } else if ((halo_model == TF17HaloModel::C1) && (disk_model == TF17DiskModel::Bd1)) {
        // disk parameters
        set_r1_disk(3 * kpc);
        set_B1_disk(24 * muG);
        set_H_disk(0.090 * kpc);
        set_phi_star_disk(-34 * M_PI / 180);
        // halo parameters
        set_z1_halo(0);
        set_B1_halo(8.2 * muG);
        set_L_halo(2.2 * kpc);
        set_phi_star_halo(197 * M_PI / 180);
        set_a_halo(0.38 / kpc / kpc);
        // shared parameters
        set_p0(-9.0 * M_PI / 180);
        set_Hp(1.2 * kpc);
        set_Lp(50 * kpc); // > 38 kpc

    } else if ((halo_model == TF17HaloModel::C1) && (disk_model == TF17DiskModel::Dd1)) {
        // disk parameters
        set_z1_disk(1.5 * kpc);
        set_B1_disk(0.40 * muG);
        set_L_disk(2.9 * kpc);
        set_phi_star_disk(120 * M_PI / 180);
        // halo parameters
        set_z1_halo(0);
        set_B1_halo(9.5 * muG);
        set_L_halo(2.1 * kpc);
        set_phi_star_halo(179 * M_PI / 180);
        set_a_halo(0.45 / kpc / kpc);
        // shared parameters
        set_p0(-8.4 * M_PI / 180);
        set_Hp(1.2 * kpc);
        set_Lp(50 * kpc); // > 30 kpc
    }

    epsilon = std::numeric_limits<double>::epsilon();
}

void TF17Field::setUseDiskField(bool use) {	useDiskField = use; }
void TF17Field::setUseHaloField(bool use) { useHaloField = use; }

bool TF17Field::isUsingDiskField() { return useDiskField; }
bool TF17Field::isUsingHaloField() { return useHaloField; }

void TF17Field::set_B1_disk(const double B1){ B1_disk = B1; }
void TF17Field::set_z1_disk(const double z1){ z1_disk = z1; }
void TF17Field::set_r1_disk(const double r1){ r1_disk = r1; }
void TF17Field::set_H_disk(const double H){ H_disk = H; }
void TF17Field::set_L_disk(const double L){ L_disk = L; }
void TF17Field::set_a_disk(const double a){ a_disk = a; }
void TF17Field::set_phi_star_disk(const double phi){ phi_star_disk = phi; }

void TF17Field::set_B1_halo(const double B1){ B1_halo = B1; }
void TF17Field::set_z1_halo(const double z1){ z1_halo = z1; }
void TF17Field::set_L_halo(const double L){ L_halo = L; }
void TF17Field::set_a_halo(const double a){ a_halo = a; }
void TF17Field::set_phi_star_halo(const double phi){ phi_star_halo = phi; }

void TF17Field::set_Hp(const double H){ H_p = H; }
void TF17Field::set_Lp(const double L){ L_p = L; }
void TF17Field::set_p0(const double p0){ 
    p_0 = p0; 
    cot_p0 = cos(p_0) / sin(p_0);
}

string TF17Field::getDiskModel() const {
    string model_name;
    switch (disk_model) {
        case TF17DiskModel::Ad1 : model_name = "Ad1"; break;
        case TF17DiskModel::Bd1 : model_name = "Bd1"; break;
        case TF17DiskModel::Dd1 : model_name = "Dd1"; break;
    }
    return model_name;
}
string TF17Field::getHaloModel() const {
    string model_name;
    switch (halo_model) {
        case TF17HaloModel::C0 : model_name = "C0"; break;
        case TF17HaloModel::C1 : model_name = "C1"; break;
    }
    return model_name;
}


Vector3d TF17Field::getField(const Vector3d& pos) const {
	double r = sqrt(pos.x * pos.x + pos.y * pos.y);  // in-plane radius
	double phi = M_PI - pos.getPhi(); // azimuth in our convention
	// double cosPhi = pos.x / r;
	double cosPhi = cos(phi);
	// double sinPhi = pos.y / r;
	double sinPhi = sin(phi);

	Vector3d b(0.);
	if (useDiskField)
		b += getDiskField(r, pos.z, phi, sinPhi, cosPhi);	// disk field
	if (useHaloField)
		b += getHaloField(r, pos.z, phi, sinPhi, cosPhi);	// halo field
	return b;
}

Vector3d TF17Field::getDiskField(const double& r, const double& z, const double& phi, const double& sinPhi, const double& cosPhi) const {
	Vector3d b(0.);
    double B_r = 0;
    double B_phi = 0;
    double B_z = 0;

    if (disk_model == TF17DiskModel::Ad1) { // ==========================================================
        if (r > r1_disk) {
            double z1_disk_z = (1. + a_disk * r1_disk * r1_disk) / (1. + a_disk * r * r); // z1_disk / z
            // B components in (r, phi, z)
            double B_r0 = radialFieldScale(B1_disk, phi_star_disk, z1_disk_z*z, phi, r, z);
            B_r = (r1_disk / r) * z1_disk_z * B_r0;
            B_z = 2 * a_disk * r1_disk * z1_disk_z*z / (1+ a_disk * r * r) * B_r0;
            B_phi = azimuthalFieldComponent(r, z, B_r, B_z);
        } else {
            // within r = r1_disk, the field lines are straight in direction g_phi + phi_star_disk
            // and thus z = z1
            double phi1_disk = shiftedWindingFunction(r1_disk, z) + phi_star_disk;
            double B_amp = B1_disk * exp(-fabs(z) / H_disk);
            B_r = cos(phi1_disk - phi) * B_amp;
            B_phi = sin(phi1_disk - phi) * B_amp;
        }

    } else if (disk_model == TF17DiskModel::Bd1) { // ===================================================
        // for model Bd1, best fit for n = 2 
        if ( r > epsilon ) {
            double r1_disk_r = r1_disk / r;	
            double z1_disk_z = 5. / (r1_disk_r*r1_disk_r + 4./sqrt(r1_disk_r)); // z1_disk / z -> remove z dependancy 
            double B_r0 = radialFieldScale(B1_disk, phi_star_disk, z1_disk_z*z, phi, r, z);
            B_r = r1_disk_r * z1_disk_z * B_r0;
            B_z = -0.4 * r1_disk_r / r * z1_disk_z* z1_disk_z * z * (r1_disk_r*r1_disk_r - 1./sqrt(r1_disk_r)) * B_r0;
        } else {
            double z1_disk_z = 5. * r*r / (r1_disk*r1_disk); // z1_disk / z -> remove z dependancy 
            double B_r0 = radialFieldScale(B1_disk, phi_star_disk, z1_disk_z*z, phi, r, z);
            B_r = 5. * r / r1_disk * B_r0;
            B_z = -10. * z / r1_disk * B_r0;
        }
        B_phi = azimuthalFieldComponent(r, z, B_r, B_z);

    } else if (disk_model == TF17DiskModel::Dd1) { // ===================================================
        // for model Dd1, best fit for n = 0.5 
        double z_sign = z >= 0 ? 1. : -1.; 
        double z_abs = fabs(z); 
        if ( z_abs > epsilon ) {
            double z1_disk_z = z1_disk / z_abs; 
            double r1_disk_r = 1.5 / (sqrt(z1_disk_z) + 0.5/z1_disk_z); // r1_disk / r
            double F_r = r1_disk_r*r  <= L_disk ? 1. : exp(1. - r1_disk_r*r/L_disk);
        // simplication of the equation in the cosinus
            double B_z0 = z_sign * B1_disk * F_r * cos(phi - shiftedWindingFunction(r, z) - phi_star_disk);
            B_r = -0.5/1.5 * r1_disk_r * r1_disk_r * r1_disk_r * r / z_abs * (sqrt(z1_disk_z) - 1/z1_disk_z) * B_z0;
            B_z = z_sign * r1_disk_r * r1_disk_r * B_z0;
        } else {
            double z_z1_disk = z_abs / z1_disk; 
            double r1_disk_r = 1.5 * sqrt(z_abs / z1_disk); // r1_disk / r
            double F_r = r1_disk_r*r  <= L_disk ? 1. : exp(1. - r1_disk_r*r/L_disk);
            double B_z0 = z_sign * B1_disk * F_r * cos(phi - shiftedWindingFunction(r, z) - phi_star_disk);
            B_r = -1.125 * r / z1_disk * (1 - 2.5 * z_z1_disk * sqrt(z_z1_disk)) * B_z0;
            B_z = z_sign * r1_disk_r * r1_disk_r * B_z0;
        }
        B_phi = azimuthalFieldComponent(r, z, B_r, B_z);
    }

    // Convert to (x, y, z) components
    b.x = - (B_r * cosPhi - B_phi * sinPhi); // flip x-component at the end
    b.y = B_r * sinPhi + B_phi * cosPhi;
    b.z = B_z;
	return b;
}

Vector3d TF17Field::getHaloField(const double& r, const double& z, const double& phi, const double& sinPhi, const double& cosPhi) const {
    int m;

	Vector3d b(0.);
	double r1_halo_r =  (1. + a_halo * z1_halo * z1_halo) / (1. + a_halo * z * z);
	// B components in (r, phi, z)
    double B_z0;

    if (halo_model == TF17HaloModel::C0) { // m = 0
        B_z0 = B1_halo * exp(-r1_halo_r*r / L_halo); 
    } else if (halo_model == TF17HaloModel::C1) { // m = 1
        // simplication of the equation in the cosinus
        double phi_prime = phi - shiftedWindingFunction(r, z) - phi_star_halo;
        B_z0 = B1_halo * exp(-r1_halo_r*r / L_halo) * cos(phi_prime); 
    }

    // Contrary to article, Br has been rewriten to a little bit by replacing
    // (2 * a * r1**3 * z) / (r**2) by (2 * a * r1**2 * z) / (r * (1+a*z**2))
    // but that is strictly equivalent except we can reintroduce the z1 in the expression via r1
	double B_r = 2 * a_halo * r1_halo_r * r1_halo_r * r * z / (1. + a_halo * z * z) * B_z0;
	double B_z = r1_halo_r * r1_halo_r * B_z0; 
	double B_phi = azimuthalFieldComponent(r, z, B_r, B_z);

	// Convert to (x, y, z) components
	b.x = - (B_r * cosPhi - B_phi * sinPhi);	// flip x-component at the end
	b.y = B_r * sinPhi + B_phi * cosPhi;
	b.z = B_z;

	return b;
}

double TF17Field::azimuthalFieldComponent(const double& r, const double& z, const double& B_r, const double& B_z) const {
	double r_ = r / L_p;
    double rscale = r > epsilon ? r_ * exp(-r_) / (1 - exp(-r_)) : 1 - r_/2. - r_*r_/12. ;
	double B_phi = cot_p0 / zscale(z) * rscale * B_r;
    B_phi = B_phi - 2 * z * r / (H_p * H_p) / zscale(z) * shiftedWindingFunction(r, z) * B_z;
	return B_phi;
}

double TF17Field::radialFieldScale(const double& B1, const double& phi_star, const double& z1, const double& phi, const double& r, const double& z) const {
    // simplication of the equation in the cosinus
    double phi_prime = phi - shiftedWindingFunction(r, z) - phi_star;
	// This term occures is parameterizations of models A and B always bisymmetric (m = 1)
	return B1 * exp(-fabs(z1) / H_disk) * cos(phi_prime);
}

double TF17Field::shiftedWindingFunction(const double& r, const double& z) const {
    return cot_p0 * log(1 - exp(-r / L_p) + epsilon) / zscale(z);
}

double TF17Field::zscale(const double& z) const {
	return 1 + z * z / H_p / H_p;
}

} // namespace crpropa
