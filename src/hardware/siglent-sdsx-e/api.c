/*
 * This file is part of the libsigrok project.
 *
 * Copyright (C) 2021 Matti Eiden <matti.eiden@bitfactor.fi>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <config.h>
#include "scpi.h"
#include "protocol.h"


static struct sr_dev_driver siglent_sdsx_e_driver_info;



static struct sr_dev_inst *probe_device(struct sr_scpi_dev_inst *scpi)
{
    struct dev_context *devc;
    struct sr_dev_inst *sdi;
    struct sr_scpi_hw_info *hw_info;
    struct sr_channel_group *cg;

    if (sr_scpi_get_hw_id(scpi, &hw_info) != SR_OK) {
        sr_info("Couldn't get IDN response.");
        return NULL;
    }

    if (strcmp(hw_info->manufacturer, "GW") != 0 ||
        strncmp(hw_info->model, "GDS-8", 5) != 0) {
        sr_scpi_hw_info_free(hw_info);
        return NULL;
    }

    sdi = g_malloc0(sizeof(struct sr_dev_inst));
    sdi->vendor = g_strdup(hw_info->manufacturer);
    sdi->model = g_strdup(hw_info->model);
    sdi->version = g_strdup(hw_info->firmware_version);
    sdi->conn = scpi;
    sdi->driver = &siglent_sdsx_e_driver_info;
    sdi->inst_type = SR_INST_SCPI;
    sdi->serial_num = g_strdup(hw_info->serial_number);
    sdi->channels = NULL;
    sdi->channel_groups = NULL;

    sr_scpi_hw_info_free(hw_info);

    devc = g_malloc0(sizeof(struct dev_context));
    //devc->frame_limit = 1;
    //devc->sample_rate = 0.0;
    //devc->df_started = FALSE;
    sdi->priv = devc;

    //sr_channel_new(sdi, 0, SR_CHANNEL_ANALOG, TRUE, "CH1");
    //sr_channel_new(sdi, 1, SR_CHANNEL_ANALOG, TRUE, "CH2");

    cg = g_malloc0(sizeof(struct sr_channel_group));
    cg->name = g_strdup("");
    cg->channels = g_slist_append(cg->channels, g_slist_nth_data(sdi->channels, 0));
    cg->channels = g_slist_append(cg->channels, g_slist_nth_data(sdi->channels, 1));
    cg->priv = NULL;
    sdi->channel_groups = g_slist_append(NULL, cg);

    return sdi;
}

static GSList *scan(struct sr_dev_driver *di, GSList *options)
{
    return sr_scpi_scan(di->context, options, probe_device);
}



static int dev_open(struct sr_dev_inst *sdi)
{
	(void)sdi;

	/* TODO: get handle from sdi->conn and open it. */

	return SR_OK;
}

static int dev_close(struct sr_dev_inst *sdi)
{
	(void)sdi;

	/* TODO: get handle from sdi->conn and close it. */

	return SR_OK;
}

static int config_get(uint32_t key, GVariant **data,
	const struct sr_dev_inst *sdi, const struct sr_channel_group *cg)
{
	int ret;

	(void)sdi;
	(void)data;
	(void)cg;

	ret = SR_OK;
	switch (key) {
	/* TODO */
	default:
		return SR_ERR_NA;
	}

	return ret;
}

static int config_set(uint32_t key, GVariant *data,
	const struct sr_dev_inst *sdi, const struct sr_channel_group *cg)
{
	int ret;

	(void)sdi;
	(void)data;
	(void)cg;

	ret = SR_OK;
	switch (key) {
	/* TODO */
	default:
		ret = SR_ERR_NA;
	}

	return ret;
}

static int config_list(uint32_t key, GVariant **data,
	const struct sr_dev_inst *sdi, const struct sr_channel_group *cg)
{
	int ret;

	(void)sdi;
	(void)data;
	(void)cg;

	ret = SR_OK;
	switch (key) {
	/* TODO */
	default:
		return SR_ERR_NA;
	}

	return ret;
}

static int dev_acquisition_start(const struct sr_dev_inst *sdi)
{
	/* TODO: configure hardware, reset acquisition state, set up
	 * callbacks and send header packet. */

	(void)sdi;

	return SR_OK;
}

static int dev_acquisition_stop(struct sr_dev_inst *sdi)
{
	/* TODO: stop acquisition. */

	(void)sdi;

	return SR_OK;
}

static struct sr_dev_driver siglent_sdsx_e_driver_info = {
	.name = "siglent-sdsx-e",
	.longname = "Siglent SDSX-E",
	.api_version = 1,
	.init = std_init,
	.cleanup = std_cleanup,
	.scan = scan,
	.dev_list = std_dev_list,
	.dev_clear = std_dev_clear,
	.config_get = config_get,
	.config_set = config_set,
	.config_list = config_list,
	.dev_open = dev_open,
	.dev_close = dev_close,
	.dev_acquisition_start = dev_acquisition_start,
	.dev_acquisition_stop = dev_acquisition_stop,
    .context = NULL,
};
SR_REGISTER_DEV_DRIVER(siglent_sdsx_e_driver_info)
