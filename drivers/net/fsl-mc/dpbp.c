// SPDX-License-Identifier: GPL-2.0+
/*
 * Freescale Layerscape MC I/O wrapper
 *
 * Copyright 2013-2016 Freescale Semiconductor, Inc.
 * Copyright 2017-2023 NXP
 */
#include <fsl-mc/fsl_mc_sys.h>
#include <fsl-mc/fsl_mc_cmd.h>
#include <fsl-mc/fsl_dpbp.h>

/**
 * dpbp_open() - Open a control session for the specified object.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @dpbp_id:	DPBP unique ID
 * @token:	Returned token; use in subsequent API calls
 *
 * This function can be used to open a control session for an
 * already created object; an object may have been declared in
 * the DPL or by calling the dpbp_create function.
 * This function returns a unique authentication token,
 * associated with the specific object ID and the specific MC
 * portal; this token must be used in all subsequent commands for
 * this specific object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpbp_open(struct fsl_mc_io *mc_io, u32 cmd_flags, int dpbp_id, u16 *token)
{
	struct dpbp_cmd_open *cmd_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_OPEN,
					  cmd_flags, 0);
	cmd_params = (struct dpbp_cmd_open *)cmd.params;
	cmd_params->dpbp_id = cpu_to_le32(dpbp_id);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	*token = mc_cmd_hdr_read_token(&cmd);

	return err;
}

/**
 * dpbp_close() - Close the control session of the object
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 *
 * After this function is called, no further operations are
 * allowed on the object without opening a new control session.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpbp_close(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
{
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_CLOSE, cmd_flags,
					  token);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpbp_create() - Create the DPBP object.
 * @mc_io:	Pointer to MC portal's I/O object
 * @dprc_token:	Parent container token; '0' for default container
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @cfg:	Configuration structure
 * @obj_id:	Returned object id; use in subsequent API calls
 *
 * Create the DPBP object, allocate required resources and
 * perform required initialization.
 *
 * This function accepts an authentication token of a parent
 * container that this object should be assigned to and returns
 * an object id. This object_id will be used in all subsequent calls to
 * this specific object.
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpbp_create(struct fsl_mc_io *mc_io, u16 dprc_token, u32 cmd_flags,
		const struct dpbp_cfg *cfg, u32 *obj_id)
{
	struct mc_command cmd = { 0 };
	int err;

	(void)(cfg); /* unused */

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_CREATE,
					  cmd_flags, dprc_token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	*obj_id = mc_cmd_read_object_id(&cmd);

	return 0;
}

/**
 * dpbp_destroy() - Destroy the DPBP object and release all its resources.
 * @mc_io:	Pointer to MC portal's I/O object
 * @dprc_token:	Parent container token; '0' for default container
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @obj_id:	ID of DPBP object
 *
 * Return:	'0' on Success; error code otherwise.
 */
int dpbp_destroy(struct fsl_mc_io *mc_io, u16 dprc_token, u32 cmd_flags,
		 u32 obj_id)
{
	struct dpbp_cmd_destroy *cmd_params;
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_DESTROY,
					  cmd_flags, dprc_token);

	cmd_params = (struct dpbp_cmd_destroy *)cmd.params;
	cmd_params->object_id = cpu_to_le32(obj_id);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpbp_enable() - Enable the DPBP.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpbp_enable(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
{
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_ENABLE, cmd_flags,
					  token);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpbp_disable() - Disable the DPBP.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpbp_disable(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
{
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_DISABLE,
					  cmd_flags, token);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpbp_reset() - Reset the DPBP, returns the object to initial state.
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpbp_reset(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token)
{
	struct mc_command cmd = { 0 };

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_RESET,
					  cmd_flags, token);

	/* send command to mc*/
	return mc_send_command(mc_io, &cmd);
}

/**
 * dpbp_get_attributes - Retrieve DPBP attributes.
 *
 * @mc_io:	Pointer to MC portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @token:	Token of DPBP object
 * @attr:	Returned object's attributes
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpbp_get_attributes(struct fsl_mc_io *mc_io, u32 cmd_flags, u16 token,
			struct dpbp_attr *attr)
{
	struct dpbp_rsp_get_attributes *rsp_params;
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_GET_ATTR,
					  cmd_flags, token);

	/* send command to mc*/
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	rsp_params = (struct dpbp_rsp_get_attributes *)cmd.params;
	attr->bpid = le16_to_cpu(rsp_params->bpid);
	attr->id = le32_to_cpu(rsp_params->id);

	return 0;
}

/**
 * dpbp_get_api_version - Get Data Path Buffer Pool API version
 * @mc_io:	Pointer to Mc portal's I/O object
 * @cmd_flags:	Command flags; one or more of 'MC_CMD_FLAG_'
 * @major_ver:	Major version of Buffer Pool API
 * @minor_ver:	Minor version of Buffer Pool API
 *
 * Return:	'0' on Success; Error code otherwise.
 */
int dpbp_get_api_version(struct fsl_mc_io *mc_io, u32 cmd_flags,
			 u16 *major_ver, u16 *minor_ver)
{
	struct mc_command cmd = { 0 };
	int err;

	/* prepare command */
	cmd.header = mc_encode_cmd_header(DPBP_CMDID_GET_API_VERSION,
					  cmd_flags, 0);

	/* send command to mc */
	err = mc_send_command(mc_io, &cmd);
	if (err)
		return err;

	/* retrieve response parameters */
	mc_cmd_read_api_version(&cmd, major_ver, minor_ver);

	return 0;
}
