#!/bin/bash

package_cloud push cogo152/gproject/ubuntu/jammy package/gctest-core_1.1.0_arm.deb
package_cloud push cogo152/gproject/ubuntu/jammy package/gctest-core_1.1.0_arm64.deb
package_cloud push cogo152/gproject/ubuntu/jammy package/gctest-core_1.1.0_amd64.deb

package_cloud push cogo152/gproject/el/8 package/gctest-core-1.1.0-1.x86_64.rpm
